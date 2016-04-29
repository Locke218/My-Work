#include "Camera.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::calcView() {
	vec3 camLoc = { 0, 0, 2 };
	vec3 camRot = { 0, 0, 0 };

	mat3 rotMat = (mat3)yawPitchRoll(camRot.y, camRot.x, camRot.z);

	vec3 eye = camLoc;
	vec3 center = eye + rotMat * vec3(0, 0, -1);
	vec3 up = rotMat * vec3(0, 1, 0);

	viewMat = glm::lookAt(eye, center, up);
}

void Camera::calcPersp() {
	float zoom = 1.f;
	int width = 800;
	int height = 600;

	float fovy = 3.14159f * .4f / zoom;
	float aspect = (float)width / (float)height;
	float zNear = .01f;
	float zFar = 1000.f;

	persMat = glm::perspective(fovy, aspect, zNear, zFar);
}

void Camera::update() {
	vec3 camVel;
	vec3 camRot = { 0, 0, 0 };

	float sens = .005;
	int w = 800, h = 600;
	double x, y;

	glfwGetCursorPos(window, &x, &y);

	camRot.y -= sens * (x - w * .5f);
	camRot.x -= sens * (y - h * .5f);
	camRot.x = glm::clamp(camRot.x, -.5f * 3.14159f, .5f * 3.14159f);

	mat3 R = (mat3)glm::yawPitchRoll(camRot.y, camRot.x, camRot.z);

	if (keyIsDown[GLFW_KEY_LEFT]) camVel += R * vec3(-1, 0, 0);
	if (keyIsDown[GLFW_KEY_RIGHT]) camVel += R * vec3(1, 0, 0);
	if (keyIsDown[GLFW_KEY_UP]) camVel += R * vec3(0, 0, -1);
	if (keyIsDown[GLFW_KEY_DOWN]) camVel += R * vec3(0, 0, 1);

	float speed = 1.f;

	if (camVel != vec3()) camVel = glm::normalize(camVel) * speed;

}
