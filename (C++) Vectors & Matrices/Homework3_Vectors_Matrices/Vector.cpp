//Author: Zane Draper
//
//Purpose: To instatiate the Vector methods
//
//*****************

#pragma once
#include "Vector.h"
#include <iostream>

using namespace std;

//BASE CONSTRUCTOR
Vector::Vector()
{
	dimensions = 0;
	data = nullptr;
}

//COPY CONSTRUCTORS
Vector::Vector(const Vector& other)
	:Vector(other.dimensions, other.data) {
}

//ASSIGNED CONNSTRUCTOR
Vector::Vector(int dimensions, float data[]) {
	init(dimensions);
	copy(data);
}

//VARIABLE CONSTRUCTOR x2
Vector::Vector(float x, float y) {
	float* tempArray = new float[2];

	tempArray[0] = x;
	tempArray[1] = y;

	data = tempArray;
	dimensions = 2;
}

//VARIABLE CONSTRUCTOR x3
Vector::Vector(float x, float y, float z) {
	float* tempArray = new float[3];

	tempArray[0] = x;
	tempArray[1] = y;
	tempArray[2] = z;

	data = tempArray;
	dimensions = 3;
}

//VARIABLE CONSTRUCTOR x4
Vector::Vector(float x, float y, float z, float w) {
	float* tempArray = new float[4];

	tempArray[0] = x;
	tempArray[1] = y;
	tempArray[2] = z;
	tempArray[3] = w;

	data = tempArray;
	dimensions = 4;
}

//DESCTRUCTOR
Vector::~Vector()
{
	clear();
}

//Empties the data and dimensions
void Vector::clear() {
	if (data != nullptr) delete[] data;

	data = nullptr;
	dimensions = 0;
}

//Copies data from another Vector
void Vector::copy(float data[]) {
	memcpy(this->data, data, dimensions * sizeof(float)); //Given by Prof
}

//Initializes the variables
void Vector::init(int dimensions) {
	//Checks for usable dimensions
	if (dimensions < 1 || dimensions > 16) {
		this->dimensions = 0;
		this->data = nullptr;
		return;
	}
	//Creates empty data
	else {
		this->dimensions = dimensions;
		float* tempArray = new float[this->dimensions];
		for (int i = 0; i < dimensions; i++) {
			float temp = 0;
			tempArray[i] = temp;
		}
		data = tempArray;
		return;
	}
}

//********************************
//
//OVERLOADED OPERATORS
//
//********************************

//output operator
ostream& operator<<(ostream& os, const Vector& vector) {
	os << "<";
	for (int i = 0; i < vector.dimensions; i++) {
		os << vector.data[i];
		if (i != (vector.dimensions - 1)) cout << ", ";
	}
	os << ">";
	return os;
}

//assignment operator
void Vector::operator=(const Vector& other) {
	this->clear();
	this->init(other.dimensions);
	this->copy(other.data);
}

//addition operator
Vector Vector::operator+(const Vector& other) const {
	if (this->dimensions == other.dimensions) {
		float* floatArray = new float[this->dimensions];

		for (int i = 0; i < this->dimensions; i++) {
			floatArray[i] = this->data[i] + other.data[i];
		}
		Vector temp(this->dimensions, floatArray);
		return temp;
	}
	else {
		Vector temp;
		return temp;
	}
}

//subtraction operator
Vector Vector::operator-(const Vector& other) const {
	if (this->dimensions == other.dimensions) {
		return (*this + (other * -1));
	}
	else {
		Vector temp;
		return temp;
	}
}

//multiplication operator
Vector Vector::operator*(float c) const {
	float* floatArray = new float[dimensions];

	for (int i = 0; i < this->dimensions; i++) {
		floatArray[i] = this->data[i] * c;
	}
	Vector temp(this->dimensions, floatArray);
	return temp;
}

//division operator
Vector Vector::operator/(float c) const {
	float temp = 1 / c;
	return (*this * temp);
}

//************************************
//
//Vector Math operations
//
//************************************

//Returns the dot products
float Vector::dotProduct(const Vector& other) const {
	if (this->dimensions == other.dimensions) {
		float temp = 0;
		for (int i = 0; i < this->dimensions; i++) {
			temp += (this->data[i] * other.data[i]);
		}
		return temp;
	}
	else {
		return -FLT_MAX;
	}
}

//Returns the cross product
Vector Vector::crossProduct(const Vector& other) const {
	if ((other.dimensions == this->dimensions) && (this->dimensions == 3)) {
		float* floatArray = new float[3];

		floatArray[0] = ((this->data[1] * other.data[2]) + (this->data[2] * other.data[1]));
		floatArray[1] = ((this->data[2] * other.data[0]) + (this->data[0] * other.data[2]));
		floatArray[2] = ((this->data[0] * other.data[1]) + (this->data[1] * other.data[0]));

		Vector temp(this->dimensions, floatArray);
		return temp;
	}
	else {
		Vector temp;
		return temp;
	}
}

//Returns magnitude
float Vector::magnitude() const {
	float tempFloat = this->dotProduct(*this);
	return sqrtf(tempFloat);
}

//returns direction vector
Vector Vector::direction() const {
	Vector temp = *this / (this->magnitude());
	return temp;
}

//Get data accessors
float* Vector::getData() const {
	return data;
}
float Vector::getData(int i) const {
	return data[i];
}

//Get Dimensions
int Vector::getDimensions() const{
	return dimensions;
}


