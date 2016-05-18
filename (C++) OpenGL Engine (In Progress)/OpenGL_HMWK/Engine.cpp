#include "Engine.h"

map<int, bool> keyIsDown;
map<int, bool> keyIsUp;
map<int, bool> keyWasDown;

void mouseClick(GLFWwindow * windowPtr, int button, int action, int mods) {
	keyIsDown[button] = action;
}

void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
	keyIsDown[key] = action;
}

Engine::Engine()
{
	texIDs = new unsigned int[2];
	
	currentTime = 0;
	previousTime = 0;

	camera = Camera();
	spacePress = 0;
	charAnim = 0;
	gameState = 0;
}

Engine::~Engine()
{
}

bool Engine::init() {
	if (glfwInit() == GL_FALSE) return false;

	GLFWwindowPtr =
		glfwCreateWindow(1200, 900, "ZaneDraper DSA1 Engine", NULL, NULL);

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

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glfwSetMouseButtonCallback(GLFWwindowPtr, mouseClick);
	glfwSetKeyCallback(GLFWwindowPtr, keyCallback);

	return true;
}

bool Engine::bufferModels() {

	if (model.buffer("box.obj")) return true;

	return false;
}

void Engine::createObjects() {

	/*for (int i = 0; i < 10; i++) {
		Object temp = Object(texIDs[0]);

		temp.transform.location = vec3(-1 + (i / 5.0f), 0 + (i / 10.0f), 0);

		objects.push_back(temp);
	}*/

	Object temp = Object(texIDs[2]);
	temp.fileName = "textures/character.png";
	temp.colType = temp.aabb;
	temp.transform.location = vec3(-1, -.5, -.2);
	temp.transform.size = vec3(.16, .16, .16);
	temp.gravityEnable = true;
	objects.push_back(temp);

	temp = Object(texIDs[1]);
	temp.fileName = "textures/character.png";
	temp.colType = temp.aabb;
	temp.transform.location = vec3(0, -1, 0);
	temp.transform.size = vec3(1, .25, .1);
	platforms.push_back(temp);

	temp = Object(texIDs[1]);
	temp.fileName = "textures/character.png";
	temp.colType = temp.aabb;
	temp.transform.location = vec3(0, .6, 0);
	temp.transform.size = vec3(1, .2, .1);
	platforms.push_back(temp);

	temp = Object(texIDs[3]);
	temp.fileName = "textures/character.png";
	temp.colType = temp.aabb;
	temp.transform.location = vec3(0, 0, -.1);
	temp.transform.size = vec3(1, 1, .1);
	platforms.push_back(temp);

	temp = Object(texIDs[4]);
	temp.fileName = "textures/character.png";
	temp.colType = temp.colliderless;
	temp.transform.location = vec3(.25, -.5, 1);
	temp.transform.size = vec3(2, 2, .1);
	menu.push_back(temp);

	Object temp2 = Object(texIDs[5]);
	temp2.fileName = "textures/character.png";
	temp2.colType = temp2.colliderless;
	temp2.transform.location = vec3(objects[0].transform.location.x + 1, objects[0].transform.location.y + .2, 1);
	temp2.transform.size = vec3(1, 1, .1);
	pause.push_back(temp2);

	addPlatform();
	addPlatform();
}

void Engine::addPlatform() {
	float length = .8 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0 - .8)));

	Object temp = Object(texIDs[1]);
	temp.fileName = "textures/character.png";
	temp.colType = temp.aabb;
	temp.transform.location = vec3(platforms[platforms.size() - 3].transform.location.x + (platforms[platforms.size() - 3].transform.size.x) + (length), platforms[platforms.size() - 3].transform.location.y - length / 5, 0);
	temp.transform.size = vec3(length, .25, .1);
	platforms.push_back(temp);

	temp = Object(texIDs[1]);
	temp.fileName = "textures/character.png";
	temp.colType = temp.aabb;
	temp.transform.location = vec3(platforms[platforms.size() - 1].transform.location.x, platforms[platforms.size() - 1].transform.location.y + 1.6, 0);
	temp.transform.size = vec3(length, .2, .1);
	platforms.push_back(temp);

	temp = Object(texIDs[3]);
	temp.fileName = "textures/character.png";
	temp.colType = temp.aabb;
	temp.transform.location = vec3(platforms[platforms.size() - 2].transform.location.x, platforms[platforms.size() - 2].transform.location.y + 1, -.1);
	temp.transform.size = vec3(length, 1, .1);
	platforms.push_back(temp);
}

void Engine::checkPlatforms() {
	if (platforms[0].transform.location.x < (objects[0].transform.location.x - platforms[0].transform.size.x/2 - 1.5)) {
		platforms.erase(platforms.begin());
		platforms.erase(platforms.begin());
		platforms.erase(platforms.begin());
		addPlatform();
	}
}

bool Engine::gameLoop() {

	currentTime = glfwGetTime();

	while (!glfwWindowShouldClose(GLFWwindowPtr))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniformMatrix4fv(4, 1, GL_FALSE, &camera.camMat[0][0]);

		vec3 lightLocation;

		if (gameState == 0) lightLocation = vec3(menu[0].transform.location.x, menu[0].transform.location.y + .2, .5);
		else if(gameState == 2) lightLocation = vec3(pause[0].transform.location.x, pause[0].transform.location.y + .2, .5);
		else lightLocation = vec3(objects[0].transform.location.x + .2, objects[0].transform.location.y + .2, .2);


		vec3 cameraLocation = vec3(objects[0].transform.location.x + 1, objects[0].transform.location.y + .2, camera.transform.location.x);

		glUniform3fvARB(5, 1, &lightLocation[0]);
		glUniform3fvARB(6, 1, &cameraLocation[0]);

		model.render(platforms, 2);
		model.render(objects, 1);

		if (gameState == 0) {
			model.render(menu, 3);
		}
		if (gameState == 2) {
			model.render(pause, 3);
		}

		update();

		//************************

		//************************

		glfwSwapBuffers(GLFWwindowPtr);

		keyWasDown = keyIsDown;
		glfwPollEvents();

		if (keyIsDown[GLFW_KEY_ESCAPE]) {
			glfwSetWindowShouldClose(GLFWwindowPtr, true);
		}

		if (gameState == 0) {

			if (keyIsDown[GLFW_KEY_ENTER]) {
				currentTime = glfwGetTime();
				gameState = 1;
			}

		}

		if (gameState == 2) {
			if (keyIsDown[GLFW_KEY_U]) {
				gameState = 1;
			}
		}

		if (gameState == 1) {
			if (keyIsDown[GLFW_MOUSE_BUTTON_2] && !keyWasDown[GLFW_MOUSE_BUTTON_2]) {
				resetTransforms();
				cout << "yes" << endl;
			}

			if (keyIsDown[GLFW_KEY_D]) {
				objects[0].transform.location.x += animRate(.3);
			}

			if (keyIsDown[GLFW_KEY_A]) {
				objects[0].transform.location.x -= animRate(.3);
			}
			if (keyIsDown[GLFW_KEY_P]) {
				gameState = 2;
				pause[0].transform.location.x = objects[0].transform.location.x + 1;
				pause[0].transform.location.y = objects[0].transform.location.y + .2;
				pause[0].transform.location.z = .1;
			}
			if (keyIsDown[GLFW_KEY_SPACE]) {
				if (spacePress < 5) {
					objects[0].rigidBody.velocity = -.012;
					objects[0].falling = true;
				}
				spacePress++;
			}
			else spacePress = 0;

			checkPlatforms();
		}
	}

	glDeleteTextures(5, texIDs);
	glBindTexture(GL_TEXTURE_2D, 0);
	glfwTerminate();

	return true;
}

bool Engine::useShaders() {
	if (shaderManager.loadShaders("shaders/vShader.glsl", "shaders/fShader.glsl")) {
		glUseProgram(shaderManager.getProgram());
		return true;
	}
	else return false;
}

bool Engine::loadTextures() {
	//Loading textures
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType("textures/texture.png", 0), "textures/texture.png");
	FIBITMAP* image2 = FreeImage_Load(FreeImage_GetFileType("textures/crate.png", 0), "textures/crate.png");
	FIBITMAP* image3 = FreeImage_Load(FreeImage_GetFileType("textures/character2.png", 0), "textures/character2.png");
	FIBITMAP* image4 = FreeImage_Load(FreeImage_GetFileType("textures/blue.png", 0), "textures/blue.png");
	FIBITMAP* image5 = FreeImage_Load(FreeImage_GetFileType("textures/intro.png", 0), "textures/intro.png");
	FIBITMAP* image6 = FreeImage_Load(FreeImage_GetFileType("textures/pause.png", 0), "textures/pause.png");

	//if (image == nullptr) cout << "Broken";
	//else cout << "working";

	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);
	FIBITMAP* image32Bit2 = FreeImage_ConvertTo32Bits(image2);
	FIBITMAP* image32Bit3 = FreeImage_ConvertTo32Bits(image3);
	FIBITMAP* image32Bit4 = FreeImage_ConvertTo32Bits(image4);
	FIBITMAP* image32Bit5 = FreeImage_ConvertTo32Bits(image5);
	FIBITMAP* image32Bit6 = FreeImage_ConvertTo32Bits(image6);

	FreeImage_Unload(image);
	FreeImage_Unload(image2);
	FreeImage_Unload(image3);
	FreeImage_Unload(image4);
	FreeImage_Unload(image5);
	FreeImage_Unload(image6);

	glGenTextures(5, texIDs);
	glBindTexture(GL_TEXTURE_2D, texIDs[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width = FreeImage_GetWidth(image32Bit);
	int height = FreeImage_GetHeight(image32Bit);
	BYTE* address = FreeImage_GetBits(image32Bit);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address);

	glBindTexture(GL_TEXTURE_2D, texIDs[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width2 = FreeImage_GetWidth(image32Bit2);
	int height2 = FreeImage_GetHeight(image32Bit2);
	BYTE* address2 = FreeImage_GetBits(image32Bit2);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width2, height2, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address2);

	glBindTexture(GL_TEXTURE_2D, texIDs[2]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width3 = FreeImage_GetWidth(image32Bit3);
	int height3 = FreeImage_GetHeight(image32Bit3);
	BYTE* address3 = FreeImage_GetBits(image32Bit3);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width3, height3, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address3);

	glBindTexture(GL_TEXTURE_2D, texIDs[3]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width4 = FreeImage_GetWidth(image32Bit4);
	int height4 = FreeImage_GetHeight(image32Bit4);
	BYTE* address4 = FreeImage_GetBits(image32Bit4);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width4, height4, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address4);

	glBindTexture(GL_TEXTURE_2D, texIDs[4]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width5 = FreeImage_GetWidth(image32Bit5);
	int height5 = FreeImage_GetHeight(image32Bit5);
	BYTE* address5 = FreeImage_GetBits(image32Bit5);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width5, height5, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address5);

	glBindTexture(GL_TEXTURE_2D, texIDs[5]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width6 = FreeImage_GetWidth(image32Bit6);
	int height6 = FreeImage_GetHeight(image32Bit6);
	BYTE* address6 = FreeImage_GetBits(image32Bit6);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width6, height6, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)address6);

	FreeImage_Unload(image32Bit);
	FreeImage_Unload(image32Bit2);
	FreeImage_Unload(image32Bit3);
	FreeImage_Unload(image32Bit4);
	FreeImage_Unload(image32Bit5);
	FreeImage_Unload(image32Bit6);

	createObjects();

	return true;
}

void Engine::update() {
	//cout << currentTime - previousTime << endl;
	previousTime = currentTime;
	currentTime = glfwGetTime();
	deltaTime = currentTime - previousTime;

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].gravityEnable == true && objects[i].falling) {
			objects[i].rigidBody.force = objects[i].rigidBody.mass * animRate(1);
			objects[i].rigidBody.velocity += (objects[i].rigidBody.force * deltaTime) / objects[i].rigidBody.mass;
			cout << objects[i].rigidBody.velocity << endl;
			objects[i].transform.location.y -= objects[i].rigidBody.velocity;
		}
		else {
			objects[i].rigidBody.velocity = 0;
		}

		Transform tForm = objects[i].transform;
		objects[i].transform.tfMatrix = translate(tForm.location) * yawPitchRoll(tForm.rotation.x, tForm.rotation.y, tForm.rotation.z) * scale(tForm.size);
	}

	objects[0].falling = true;

	for (int i = 0; i < platforms.size(); i++) {
		if (i%3 == 0 && platforms[i].collidesWith(objects[0])) {
			objects[0].falling = false;
		}

		Transform tForm = platforms[i].transform;
		platforms[i].transform.tfMatrix = translate(tForm.location) * yawPitchRoll(tForm.rotation.x, tForm.rotation.y, tForm.rotation.z) * scale(tForm.size);

	}

    camera.update(GLFWwindowPtr, keyIsDown, 1/(currentTime - previousTime));
	camera.transform.location.x = objects[0].transform.location.x + 1;
	camera.transform.location.y = objects[0].transform.location.y + .2;


	Transform tForm = pause[0].transform;
	pause[0].transform.tfMatrix = translate(tForm.location) * yawPitchRoll(tForm.rotation.x, tForm.rotation.y, tForm.rotation.z) * scale(tForm.size);

	if (objects[0].falling == true) {
		objects[0].transform.rotation = vec3(0, -1.5705, 0);
	}
	else if (keyIsDown[GLFW_KEY_D]) {
		charAnim += animRate(10);
		if (charAnim >= 1) {
			objects[0].transform.rotation.y += 1.57075;
			charAnim = 0;
		}
	}
}

void Engine::resetTransforms() {
	/*

	for (int i = 0; i < 10; i++) {
		objects[i].reset();
		objects[i].transform.location = vec3(-1 + (i / 5.), 0 + (i / 10.), 0);
	}

	*/
}

float Engine::animRate(float input) {
	float rate = 1 / (currentTime - previousTime);
	//cout << rate << endl;
	return (input / rate);
}