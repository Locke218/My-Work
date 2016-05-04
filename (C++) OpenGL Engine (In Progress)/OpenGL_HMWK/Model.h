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
#include "Object.h"

using namespace std;
using namespace glm;

class Model
{
public:
	Model();
	~Model();
	bool buffer();
	void render(vector<Object>& objects);
private:
	GLuint vertArr;
	unsigned int vertCount;
};

