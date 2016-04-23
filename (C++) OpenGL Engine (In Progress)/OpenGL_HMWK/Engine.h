//AUTHOR: Zane Draper
//
//PURPOSE: Declaring Engine methods and variables
//
//**********************************

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>

#include <map>
#include <iostream>
#include <vector>

#include "Object.h"
#include "ShaderManager.h"

using namespace std;
using namespace glm;

#pragma once

//Main engine class
class Engine
{
public:
	//Methods
	Engine();
	~Engine();
	bool init();
	bool bufferModel();
	bool gameLoop();
	bool useShaders();
	bool loadTextures();
	void update();
	void resetTransforms();

	//Variables
	unsigned int* texIDs;
	bool swap;
	float currentTime;
	float previousTime;
	float deltaTime;

	//Vector array of objects
	vector<Object> objects;

private:
	//Variables
	GLFWwindow* GLFWwindowPtr;
	GLuint vertArr;
	unsigned int vertCount;
	ShaderManager shaderManager;
};

