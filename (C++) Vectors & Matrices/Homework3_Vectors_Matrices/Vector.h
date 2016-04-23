//Author: Zane Draper
//
//Purpose: To declare the Vector methods and variables
//
//*****************

#pragma once
#include <iostream>

class Vector
{
public:
	//Constructors
	Vector();
	Vector(const Vector& other);
	Vector(int dimensions, float data[]);
	Vector(float x, float y);
	Vector(float x, float y, float z);
	Vector(float x, float y, float z, float w);
	//Destructors
	~Vector();

	//Methods
	float* getData() const;
	float getData(int i) const;
	int getDimensions() const;
	void clear();
	void copy(float data[]);
	void init(int dimensions);

	//Overloaded operators
	void operator=(const Vector& other);
	Vector operator+(const Vector& other) const;
	Vector operator-(const Vector& other) const;
	Vector operator*(float c) const;
	Vector operator/(float c) const;
	friend std::ostream& operator<<(std::ostream& os, const Vector& vector);

	//Math operations
	float dotProduct(const Vector& other) const;
	Vector crossProduct(const Vector& other) const;
	float magnitude() const;
	Vector direction() const;

private:
	//Variables
	int dimensions;
	float* data;
};

