//AUTHOR: Zane Draper
//
//PURPOSE: Declares all methods and variables for shaderManager
//
//**********************************

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>

#include <string>
#include <fstream>
#include <iostream>

#pragma once
using namespace std;

class ShaderManager
{
public:
	//Methods
	ShaderManager();
	~ShaderManager();
	GLuint getProgram() const;
	//Variables
	bool loadShaders(const char* vertexFile, const char* fragmentFile);
private:
	//Methods
	GLuint loadShader(const char* file, GLenum shaderType);
	//Variable
	GLuint program;
};

