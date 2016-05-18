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
#include <fstream>
#include <sstream>

#include "Structs.h"
#include "Object.h"

using namespace std;
using namespace glm;

class Model
{
public:
	Model();
	~Model();
	bool buffer(string objFile);
	void render(vector<Object>& objects, int numOpt);
private:
	GLuint vertArr;
	GLuint vertArr2;
	unsigned int vertCount;
	unsigned int vertCount2;
};

