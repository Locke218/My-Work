#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <map>
#include <iostream>
#include <vector>

using namespace std;
using namespace glm;

struct Vertex {
	vec3 loc;
	vec2 uv;
};

struct Transform {
	vec3 location;
	vec3 rotation;
	vec3 size;
	mat4 tfMatrix;
};

struct RigidBody {
	float velocity;
	float force;
	float mass;
};