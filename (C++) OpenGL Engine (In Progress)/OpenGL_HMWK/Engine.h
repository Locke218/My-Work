#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>

#include <map>
#include <iostream>
#include <vector>

#include "Structs.h"
#include "Object.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "InputController.h"
#include "Model.h"

using namespace std;
using namespace glm;

class Engine
{
public:
	Engine();
	~Engine();
	bool init();
	bool bufferModels();
	bool gameLoop();
	bool useShaders();
	bool loadTextures();
	void update();
	void resetTransforms();
	void createObjects();
	void addPlatform();
	void checkPlatforms();
	float animRate(float input);
	unsigned int* texIDs;
	vector<Object> objects;
	vector<Object> platforms;
	vector<Object> menu;
	vector<Object> pause;
	vector<Object> enemies;
	Model model;

	float currentTime;
	float previousTime;
	float deltaTime;
	mat4 camMat;
	Camera camera;
	InputController *input;
	int spacePress;
	float charAnim;

	float gameState;

private:
	GLFWwindow* GLFWwindowPtr;
	ShaderManager shaderManager;
};

