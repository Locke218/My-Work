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

using namespace std;
using namespace glm;

#pragma once

class Camera
{
public:
	Camera();
	~Camera();

	void calcView();
	void calcPersp();
	void update();

	mat4 persMat;
	mat4 viewMat;
	mat4 camMat;
};

