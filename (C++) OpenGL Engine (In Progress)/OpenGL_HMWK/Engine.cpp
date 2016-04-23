//AUTHOR: Zane Draper
//
//PURPOSE: Creates individual objects to be displayed in game
//
//**********************************

#include "Engine.h"

//creates maps for key input
map<int, bool> keyIsDown;
map<int, bool> keyIsUp;
map<int, bool> keyWasDown;

//keeps track of key presses
void mouseClick(GLFWwindow * windowPtr, int button, int action, int mods) {
	keyIsDown[button] = action;
}

//keeps track of key presses
void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	keyIsDown[key] = action;
}

//Engine Constructor
Engine::Engine()
{
	//sets up array of texture ID's
	texIDs = new unsigned int[2];

	//creates 10 objects for displaying functionality
	for (int i = 0; i < 10; i++) {
		Object temp;

		temp.transform.location = vec3(-1 + (i / 5.0f), 0 + (i / 10.0f), 0);

		objects.push_back(temp);
	}

	//creates a main player object for implementing movement later
	Object temp;
	temp.fileName = "textures/character.png";
	temp.transform.location = vec3(0, 0, 0);
	temp.transform.size = vec3(.05, .05, .05);
	objects.push_back(temp);

	//sets timer for gravity and movement
	currentTime = 0;
	previousTime = 0;
}

//Engine Destructor
Engine::~Engine()
{
}

//Initializes the Engine, creating window and making sure everything is set up
bool Engine::init() {
	if (glfwInit() == GL_FALSE) return false;

	GLFWwindowPtr =
		glfwCreateWindow(800, 600, "ZaneDraper DSA1 Engine", NULL, NULL);

	if (GLFWwindowPtr != nullptr)
		glfwMakeContextCurrent(GLFWwindowPtr);
	else {
		glfwTerminate();
		return false;
	}

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return false;
	}

	swap = true;

	return true;
}

//Creates the vertices and vertex array data
bool Engine::bufferModel() {

	vector< vec3> locs =
	{ { 1, 1, 0 },
	{ -1, 1, 0 },
	{ -1, -1, 0 },
	{ 1, -1, 0 }, };

	vector< vec2> uvs =
	{ { 1, 1},
	{ 0, 1},
	{ 0, 0},
	{ 1, 0}, };

	vector <unsigned int> locInds =
	{ 0, 1, 2, 0, 2, 3 };

	vertCount = locInds.size();

	vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++) {
		vertBufData[i].loc = locs[locInds[i]];
		vertBufData[i].uv = uvs[locInds[i]];
	}

	GLuint vertBuf;

	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) *vertCount,
		&vertBufData[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		0);

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)sizeof( vec3));

	glBindVertexArray(0);

	glfwSetMouseButtonCallback(GLFWwindowPtr, mouseClick);
	glfwSetKeyCallback(GLFWwindowPtr, keyCallback);

	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);


	return true;
}

//This is the loop that runs indefinitely
bool Engine::gameLoop() {

	//gets the current time since glfw initialization
	currentTime = glfwGetTime();

	//keeps running till told that window should close
	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{
		//clears the background
		glClear(GL_COLOR_BUFFER_BIT);

		//updates the objects
		update();

		glBindVertexArray(vertArr);

		//swaps between textures
		if(swap == true)
			glBindTexture(GL_TEXTURE_2D, texIDs[0]);
		else glBindTexture(GL_TEXTURE_2D, texIDs[1]);

		//draws the objects in the objects array
		for (int i = 0; i < 11; i++) {
			glUniformMatrix4fv(2, 1, GL_FALSE, &objects[i].transform.tfMatrix[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, vertCount);
		}
		glBindVertexArray(0);

		glfwSwapBuffers(GLFWwindowPtr);

		//checks for keys
		keyWasDown = keyIsDown;
		glfwPollEvents();

		if (keyIsDown[GLFW_KEY_ESCAPE]) {
			glfwSetWindowShouldClose(GLFWwindowPtr, true);
		}

		if (keyIsDown[GLFW_MOUSE_BUTTON_1] && !keyWasDown[GLFW_MOUSE_BUTTON_1]) {
			if (swap == true) swap = false;
			else swap = true;
		}
		if (keyIsDown[GLFW_MOUSE_BUTTON_2] && !keyWasDown[GLFW_MOUSE_BUTTON_2]) {
			resetTransforms();
		}
	}

	//on close, unbind and delete textures
	glDeleteTextures(1, texIDs);
	glBindTexture(GL_TEXTURE_2D, 0);
	glfwTerminate();

	return true;
}

//loads the shaders when initialized, returns false if any problems
bool Engine::useShaders() {
	if (shaderManager.loadShaders("shaders/vShader.glsl", "shaders/fShader.glsl")) {
		glUseProgram(shaderManager.getProgram());
		return true;
	}
	else return false;
}

//Loads all the textures for the objects
bool Engine::loadTextures() {

	//Loading textures
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType("textures/texture.png", 0), "textures/texture.png");
	FIBITMAP* image2 = FreeImage_Load(FreeImage_GetFileType("textures/texture2.png", 0), "textures/texture2.png");

	//converts iamge types
	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);
	FIBITMAP* image32Bit2 = FreeImage_ConvertTo32Bits(image2);

	//releases the original versions
	FreeImage_Unload(image);
	FreeImage_Unload(image2);

	//creates 2 textures
	glGenTextures(2, texIDs);

	//loading in texture 1
	glBindTexture(GL_TEXTURE_2D, texIDs[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width = FreeImage_GetWidth(image32Bit);
	int height = FreeImage_GetHeight(image32Bit);
	BYTE* address = FreeImage_GetBits(image32Bit);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address);

	//loading in texture 2
	glBindTexture(GL_TEXTURE_2D, texIDs[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width2 = FreeImage_GetWidth(image32Bit2);
	int height2 = FreeImage_GetHeight(image32Bit2);
	BYTE* address2 = FreeImage_GetBits(image32Bit2);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width2, height2, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address2);

	//after binding, release both images
	FreeImage_Unload(image32Bit);
	FreeImage_Unload(image32Bit2);

	return true;
}

//Updates the object sin the array
void Engine::update() {
	//gets time and time between frames
	previousTime = currentTime;
	currentTime = glfwGetTime();
	deltaTime = currentTime - previousTime;

	//cycles through all objects in scene
	for (int i = 0; i < 11; i++) {

		//if one of the initial 10, enact gravity
		if (i < 10) {
			objects[i].rigidBody.force = objects[i].rigidBody.mass * .1;
			objects[i].rigidBody.velocity += (objects[i].rigidBody.force * deltaTime) / objects[i].rigidBody.mass;
			objects[i].transform.location.y -= objects[i].rigidBody.velocity;
			if (objects[i].transform.location.y <= -1) objects[i].transform.location.y = -1;
		}

		//for all, place in the correct location
		Transform tForm = objects[i].transform;
		objects[i].transform.tfMatrix = translate(tForm.location) * yawPitchRoll(tForm.rotation.x, tForm.rotation.y, tForm.rotation.z) * scale(tForm.size);
	}

	//check for collisions
	for (int i = 0; i < 10; i++) {
		if (objects[i].collidesWith(objects[10])) {
			cout << " " << i << ": Collision" << endl;
		}
	}

}

//resets the location of the initial 10 objects for testing purposes
void Engine::resetTransforms() {
	for (int i = 0; i < 10; i++) {
		objects[i].reset();
		objects[i].transform.location = vec3(-1 + (i / 5.), 0 + (i / 10.), 0);
	}
}