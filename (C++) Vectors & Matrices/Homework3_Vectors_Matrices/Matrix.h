//Author: Zane Draper
//
//Purpose: To declare MAtrix methods and variables
//
//*****************

#pragma once
#include "Vector.h"
using namespace std;

class Matrix
{
public:
	//Constructors
	Matrix();
	Matrix(Vector row0, Vector row2, Vector row3, Vector row4);
	//Desctructors
	~Matrix();

	//Methods
	float* getData();
	Matrix transpose(Vector col1, Vector col2, Vector col3, Vector col4);
	Vector row(int i) const;
	Vector column(int i) const;

	//Overloaded operators
	Matrix operator*(const Matrix& other) const;
	Vector operator*(const Vector& other) const;
	Matrix operator*(float c) const;

	//friend std::ostream& operator<<(std::ostream& os, const Vector& vector);

private:
	//Variables
	float data[16] = {};


};

