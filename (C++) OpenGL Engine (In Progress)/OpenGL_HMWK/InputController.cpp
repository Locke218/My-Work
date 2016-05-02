#include "InputController.h"

InputController* InputController::input_instance = NULL;

InputController* InputController::instance() {
	 if (!instance) {
		 input_instance = new InputController;
	 }
	 return input_instance;
}

bool InputController::getKeyIsDown(int i) {
	return keyIsDown[i];
}
void InputController::setKeyIsDown(int i, bool status) {
	keyIsDown[i] = status;
}
void InputController::setKeyWasDown() {
	keyWasDown = keyIsDown;
}