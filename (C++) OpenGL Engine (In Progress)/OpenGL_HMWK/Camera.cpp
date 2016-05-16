#include "Camera.h"

Camera::Camera()
{

	transform.location = vec3( .2921, -.0789, -.0096 );
	transform.rotation = vec3( 0.1668, 1.5582, 0);
	transform.size = { .25, .25, .25 };

	rigidbody.force = 0;
	rigidbody.mass = .1;
	rigidbody.velocity = 0;

	calcPersp();
	calcView();
	updateMatrix();
}


Camera::~Camera()
{
}

void Camera::calcView() {

	mat3 rotMat = (mat3)yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z);

	vec3 eye = transform.location;
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

void Camera::updateMatrix() {
	camMat = persMat * viewMat;
}

void Camera::update(GLFWwindow *window, map<int, bool> keys, float rate) {

	if (keys[GLFW_MOUSE_BUTTON_RIGHT]) {

		vec3 camVel = vec3(0, 0, 0);

		float sens = .001f;
		int w = 800, h = 600;
		double x, y;

		glfwGetCursorPos(window, &x, &y);

		transform.rotation.y -= animRate(sens * (x - w * .5f), rate);
		transform.rotation.x -= animRate(sens * (y - h * .5f), rate);
		transform.rotation.x = glm::clamp(transform.rotation.x, -.5f * 3.14159f, .5f * 3.14159f);

		mat3 R = (mat3)glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z);

		if (keys[GLFW_KEY_LEFT]) camVel += R * vec3(-1, 0, 0);
		if (keys[GLFW_KEY_RIGHT]) camVel += R * vec3(1, 0, 0);
		if (keys[GLFW_KEY_UP]) camVel += R * vec3(0, 0, -1);
		if (keys[GLFW_KEY_DOWN]) camVel += R * vec3(0, 0, 1);

		float speed = .10f;

		if (camVel != vec3()) camVel = glm::normalize(camVel) * animRate(speed, rate);

		transform.location += camVel;
	}

	calcPersp();
	calcView();
	updateMatrix();
}

float Camera::animRate(float input, float rate) {
	return (input / rate);
}
