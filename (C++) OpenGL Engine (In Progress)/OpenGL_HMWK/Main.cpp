//AUTHOR: Zane Draper
//
//PURPOSE: Initializes the game and runs the loop
//
//**********************************

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <FreeImage.h>

#include <iostream>
#include <vector>

#include "Engine.h"

using namespace std;

int main()
{
	//create engine and check for functionality, end if any problems
	Engine engine;
	if (!engine.init()) return -1;
	if (!engine.bufferModel()) return -1;

	//load any shaders
	engine.useShaders();

	//loads the textures for objects
	engine.loadTextures();

	//starts the game loop
	engine.gameLoop();

	//reaches here after the game loop has ended, ends program
	return 0;
}