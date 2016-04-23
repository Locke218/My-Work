//AUTHOR: Zane Draper
//
//PURPOSE: Declares variables and methods for the objects
//
//**********************************

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
	//Methods
	Object();
	~Object();
	void reset();
	bool collidesWith(const Object &object);

	//Enum for the collision type
	enum CollisionType {
		colliderless,
		aabb,
		sphere,
	};

	//Variables on objects
	Transform transform;
	string fileName;
	RigidBody rigidBody;
	CollisionType colType;
};

