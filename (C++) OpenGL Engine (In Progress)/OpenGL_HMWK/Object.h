#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <FreeImage.h>

#include <math.h>
#include <map>
#include <iostream>
#include <vector>

#include "Structs.h"
#include "ShaderManager.h"

using namespace std;
using namespace glm;

#pragma once

class Object
{
public:
	Object();
	Object(unsigned int texNum);
	~Object();
	void reset();
	bool collidesWith(const Object &object);
	unsigned int texID;

	enum CollisionType {
		colliderless,
		aabb,
		sphere,
	} colType;

	Transform transform;
	string fileName;
	RigidBody rigidBody;
	bool gravityEnable;
	bool falling;
};

