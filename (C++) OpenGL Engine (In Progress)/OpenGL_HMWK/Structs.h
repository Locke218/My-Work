#pragma once

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

namespace Input {
	
}


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

class Input {
	map<int, bool> keyIsDown;
	map<int, bool> keyIsUp;
	map<int, bool> keyWasDown;

	static Input *instance;

	public:
		void mouseClick(GLFWwindow * windowPtr, int button, int action, int mods) {
			keyIsDown[button] = action;
		}

		void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods) {
			keyIsDown[key] = action;
		}
};