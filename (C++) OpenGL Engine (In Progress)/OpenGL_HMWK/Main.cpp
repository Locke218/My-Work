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
	Engine engine;
	if (!engine.init()) return -1;
	if (!engine.bufferModels()) return -1;

	engine.useShaders();

	engine.loadTextures();

	engine.gameLoop();

	return 0;
}