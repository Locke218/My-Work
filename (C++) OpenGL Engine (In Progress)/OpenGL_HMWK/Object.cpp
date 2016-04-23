//AUTHOR: Zane Draper
//
//PURPOSE: Creates individual objects to be displayed in game
//
//**********************************

#include "Object.h"

//Object Constructor
Object::Object()
{
	fileName = "textures/texture.png";

	//Sets initial object location, size and rotation
	transform.size = vec3(.025, .025, .025);
	transform.location = vec3(0, 0, 0);
	transform.rotation = vec3(0, 0, 0);

	//initiallizes the movement of the object
	rigidBody.force = 0;
	rigidBody.mass = .1;
	rigidBody.velocity = 0;

	//sets the initial collision type
	colType = sphere;
}

//Object deconstructor
Object::~Object()
{

}

//reset the location and movement of the object
void Object::reset() {
	transform.location = vec3(0, 0, 0);
	rigidBody.velocity = 0;
	rigidBody.force = 0;
}

//Checks for collision with other objects
bool Object::collidesWith(const Object &object) {

	//If either object has no collider, there can be no collision
	if (colType == colliderless || object.colType == colliderless) {
		return false;
	}
	//Checks for collision between two spheres
	if (colType == sphere && object.colType == sphere) {
		float collideDistance = (transform.size.x + object.transform.size.x) * (transform.size.x + object.transform.size.x);
		float actualDistance = ((transform.location.x - object.transform.location.x) * (transform.location.x - object.transform.location.x)) +
			((transform.location.y - object.transform.location.y) * (transform.location.y - object.transform.location.y));

		if (actualDistance > collideDistance) {
			return false;
		}
	}
	//checks for collision between two box colliders
	if (colType == aabb && object.colType == aabb) {
		//cout << "aabb";
		if ( (fabs(transform.location.x - object.transform.location.x)) > (transform.size.x + object.transform.size.x)) return false;
		if( (fabs(transform.location.y - object.transform.location.y)) > (transform.size.y + object.transform.size.y)) return false;
		if( (fabs(transform.location.z - object.transform.location.z)) > (transform.size.z + object.transform.size.z)) return false;
	}
	//checks for collision between a sphere and a box collider
	if (colType == sphere && object.colType == aabb) {

		int distance = 0;

		if (transform.location.x < (object.transform.location.x - object.transform.size.x)) {
			distance += (((object.transform.location.x - object.transform.size.x) - transform.location.x) * ((object.transform.location.x - object.transform.size.x) - transform.location.x));
		}
		else if (transform.location.x >(object.transform.location.x + object.transform.size.x)) {
			distance += ((transform.location.x - (object.transform.location.x + object.transform.size.x)) * (transform.location.x - (object.transform.location.x + object.transform.size.x)));
		}
		if (transform.location.y < (object.transform.location.y - object.transform.size.y)) {
			distance += (((object.transform.location.y - object.transform.size.y) - transform.location.y) * ((object.transform.location.y - object.transform.size.y) - transform.location.y));
		}
		else if (transform.location.y >(object.transform.location.y + object.transform.size.y)) {
			distance += ((transform.location.y - (object.transform.location.y + object.transform.size.y)) * (transform.location.y - (object.transform.location.y + object.transform.size.y)));
		}
		if (transform.location.z < (object.transform.location.z - object.transform.size.z)) {
			distance += (((object.transform.location.z - object.transform.size.z) - transform.location.z) * ((object.transform.location.z - object.transform.size.z) - transform.location.z));
		}
		else if (transform.location.z >(object.transform.location.z + object.transform.size.z)) {
			distance += ((transform.location.z - (object.transform.location.z + object.transform.size.z)) * (transform.location.z - (object.transform.location.z + object.transform.size.z)));
		}

		if (distance < (transform.size.x * transform.size.x)) {
			return false;
		}
	}
	//checks for the other combo of box and sphere (note: condense)
	else if (object.colType == sphere && colType == aabb) {

		int distance = 0;

		if (object.transform.location.x < (transform.location.x - transform.size.x)) {
			distance += (((transform.location.x - transform.size.x) - object.transform.location.x) * ((transform.location.x - transform.size.x) - object.transform.location.x));
		}
		else if (object.transform.location.x >(transform.location.x + transform.size.x)) {
			distance += ((object.transform.location.x - (transform.location.x + transform.size.x)) * (object.transform.location.x - (transform.location.x + transform.size.x)));
		}
		if (object.transform.location.y < (transform.location.y - transform.size.y)) {
			distance += (((transform.location.y - transform.size.y) - object.transform.location.y) * ((transform.location.y - transform.size.y) - object.transform.location.y));
		}
		else if (object.transform.location.y >(transform.location.y + transform.size.y)) {
			distance += ((object.transform.location.y - (transform.location.y + transform.size.y)) * (object.transform.location.y - (transform.location.y + transform.size.y)));
		}
		if (object.transform.location.z < (transform.location.z - transform.size.z)) {
			distance += (((transform.location.z - transform.size.z) - object.transform.location.z) * ((transform.location.z - transform.size.z) - object.transform.location.z));
		}
		else if (object.transform.location.z >(transform.location.z + transform.size.z)) {
			distance += ((object.transform.location.z - (transform.location.z + transform.size.z)) * (object.transform.location.z - (transform.location.z + transform.size.z)));
		}

		if (distance < (object.transform.size.x * object.transform.size.x)) {
			return false;
		}
	}
	//if these any of these are actually true and colliding
	return true;
}
