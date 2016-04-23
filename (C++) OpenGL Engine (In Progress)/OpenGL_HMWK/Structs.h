//AUTHOR: Zane Draper
//
//PURPOSE: A more conventient location for my structs
//
//**********************************

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <map>
#include <iostream>
#include <vector>

#include "ShaderManager.h"

using namespace std;
using namespace glm;

#pragma once

//This is for loading in vertex shaders
struct Vertex {
	vec3 loc;
	vec2 uv;
};

//This is for object display information
struct Transform {
	vec3 location;
	vec3 rotation;
	vec3 size;
	mat4 tfMatrix;
};

//This is for object movement
struct RigidBody {
	float velocity;
	float force;
	float mass;
};