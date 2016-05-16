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
#include "InputController.h"

using namespace std;
using namespace glm;

class Camera
{
public:
	Camera();
	~Camera();

	void calcView();
	void calcPersp();
	void updateMatrix();
	void update(GLFWwindow *window, map<int, bool> keys, float rate);
	float animRate(float input, float rate);

	mat4 persMat;
	mat4 viewMat;

	mat4 camMat;
	Transform transform;
	RigidBody rigidbody;

	float fovy;
	float aspect;
	float zNear;
	float zFar;
};

