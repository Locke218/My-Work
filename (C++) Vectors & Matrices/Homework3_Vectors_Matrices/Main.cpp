//Author: Zane Draper
//
//Purpose: To run the program
//
//*****************

#pragma once
#include "Vector.h"
#include "Matrix.h"

using namespace std;

int main() {

	//Code for test Vector
	Vector a = Vector(1, 0, 0);
	Vector b = Vector(0, 2, 0);

	//Testing
	Vector c = a - b;
	cout << c << endl;

	c = a.crossProduct(b);
	cout << c.magnitude() << "\n" << c.direction() << endl;

	float arr[16];
	for (int i = 0; i < 16; i++) arr[i] = (float)i;
	c = Vector(16, arr);
	cout << c << endl;

	//Code for test Matrix
	Matrix m = Matrix(Vector(1, 0, 0, 1), Vector(0, 1, 0, 2), Vector(0, 0, 1, 3), Vector(0, 0, 0, 1));

	//Testing
	Vector v = Vector(1, 0, -1);

	Vector u = m*v;
	cout << u << endl;

	v = Vector(1, 0, -1, 1);
	u = m*v;
	cout << u << endl;

	v = Vector(1, 0, -1, 0);
	u = m*v;
	cout << u << endl;

	cin.get();

}