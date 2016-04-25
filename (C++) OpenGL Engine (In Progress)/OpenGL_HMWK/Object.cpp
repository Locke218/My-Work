#include "Object.h"


Object::Object()
{
	fileName = "textures/texture.png";
	transform.size = vec3(.025, .025, .025);
	transform.location = vec3(0, 0, 0);
	transform.rotation = vec3(0, 0, 0);

	rigidBody.force = 0;
	rigidBody.mass = .1;
	rigidBody.velocity = 0;

	colType = sphere;
}


Object::~Object()
{

}

void Object::reset() {
	transform.location = vec3(0, 0, 0);
	rigidBody.velocity = 0;
	rigidBody.force = 0;
}

bool Object::collidesWith(const Object &object) {
	if (colType == colliderless || object.colType == colliderless) {
		return false;
	}
	else if (colType == sphere && object.colType == sphere) {
		
		float collideDistance = (transform.size.x + object.transform.size.x);

		if (glm::distance(transform.location, object.transform.location) > collideDistance) {
			return false;
		}

	}
	else if (colType == aabb && object.colType == aabb) {

		for (int i = 0; i < 3; i++) {
			if ((fabs(transform.location[i] - object.transform.location[i])) >(transform.size[i] + object.transform.size[i])) return false;
		}

	}
	else {
		int distance = 0;

		Transform tempAABB;
		Transform tempSphere;

		if (object.colType == aabb) {
			tempAABB = object.transform;
			tempSphere = transform;
		}
		else {
			tempAABB = transform;
			tempSphere = object.transform;
		}

		cout << "AAB?: " << tempAABB.location.y;
		cout << "Sphere?: " << tempSphere.location.y;

		for (int i = 0; i < 3; i++ ) {
			float max = tempAABB.location[i] + tempAABB.size[i];
			float min = tempAABB.location[i] - tempAABB.size[i];
			float current = tempSphere.location[i];

			if (tempSphere.location[i] < min) {
				distance += pow(min - current, 2);
			}
			else if (tempSphere.location[i] > max) {
				distance += pow(current - min, 2);
			}
		}

		if (distance < (tempSphere.size.x * tempSphere.size.x)) {
			return false;
		}
	}
	return true;
}
