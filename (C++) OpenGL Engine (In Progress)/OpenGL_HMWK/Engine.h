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

using namespace std;
using namespace glm;

class Engine
{
public:
	Engine();
	~Engine();
	bool init();
	bool bufferModel();
	bool gameLoop();
	bool useShaders();
	bool loadTextures();
	void update();
	void resetTransforms();
	unsigned int* texIDs;
	bool swap;
	vector<Object> objects;

	float currentTime;
	float previousTime;
	float deltaTime;
	mat4 camMat;
	Camera camera;
	InputController *input;

private:
	GLFWwindow* GLFWwindowPtr;
	GLuint vertArr;
	unsigned int vertCount;
	ShaderManager shaderManager;
};

