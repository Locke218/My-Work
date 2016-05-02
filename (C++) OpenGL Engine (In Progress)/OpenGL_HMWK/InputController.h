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

class InputController {

	public:
		map<int, bool> keyIsDown;
		map<int, bool> keyIsUp;
		map<int, bool> keyWasDown;

		bool getKeyIsDown(int i);
		void setKeyIsDown(int i, bool status);
		void setKeyWasDown();
		

		static InputController* instance();

	private:
		static InputController* input_instance;
		InputController() {};
		~InputController() {};

};
