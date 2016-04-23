//Author: Zane Draper
//
//Purpose: To instatiate MAtrix methods
//
//*****************

#pragma once
#include "Matrix.h"

//BASE CONSTRUCTOR
Matrix::Matrix()
{
	Vector row0 = Vector(1, 0, 0, 0);
	Vector row1 = Vector(0, 1, 0, 0);
	Vector row2 = Vector(0, 0, 1, 0);
	Vector row3 = Vector(0, 0, 0, 1);

	Matrix(row0, row1, row2, row3);
}

//ASSIGNED CONSTRUCTOR
Matrix::Matrix(Vector row0, Vector row1, Vector row2, Vector row3) {
	if ((row0.getDimensions() == 4) && (row1.getDimensions() == 4) && (row2.getDimensions() == 4) && (row3.getDimensions() == 4)) {
		for (int i = 0; i < 4; i++) {
			data[i] = row0.getData(i);
		}
		for (int i = 0; i < 4; i++) {
			data[i + 4] = row1.getData(i);
		}
		for (int i = 0; i < 4; i++) {
			data[i + 8] = row2.getData(i);
		}
		for (int i = 0; i < 4; i++) {
			data[i + 12] = row3.getData(i);
		}
	}
	else {
		Matrix();
	}

}

//DESTRUCTOR
Matrix::~Matrix()
{

}

//Return data accessor
float* Matrix::getData() {
	float* tempArray = data;
	return tempArray;
}

//Transposes the Matrix
Matrix Matrix::transpose(Vector col1, Vector col2, Vector col3, Vector col4) {
	Matrix tempMatrix;
	Vector* vectors = new Vector[4];

	for (int i = 0; i < 4; i++) {
		float temp1 = data[i];
		float temp2 = data[i+4];
		float temp3 = data[i+8];
		float temp4 = data[i+12];
		vectors[i] = Vector(0, 0, 0, 0);
	}

	return Matrix(vectors[0], vectors[1], vectors[2], vectors[3]);
}

//Returns the requested row
Vector Matrix::row(int i) const{
	float* tempArray = new float[4];

	for (int j = 0; j < 4; j++) {
		tempArray[j] = data[(j + (i * 4))];
	}


	Vector tempRow = Vector(4, tempArray);
	return tempRow;
}

//Returns the requested columns
Vector Matrix::column(int i) const {
	float* tempArray = new float[4];

	for (int j = 0; j < 4; j++) {
		tempArray[j] = data[(i + (j * 4))];
	}


	Vector tempCol = Vector(4, tempArray);
	return tempCol;
}


//**************************************
//
//Overloaded Operators
//
//**************************************

//Multiple with other matrix
Matrix Matrix::operator*(const Matrix& other) const {
	Matrix tempMatrix;
	for (int i = 0; i < 4; i++) {
		Vector tempVector = row(i);
		for (int j = 0; j < 4; j++) {
			Vector tempColumn = column(j);
			tempMatrix.data[j + (i *4)] = (tempVector.getData(j) *tempColumn.getData(j)) + (tempVector.getData(j) *tempColumn.getData(j)) + (tempVector.getData(j) *tempColumn.getData(j)) + (tempVector.getData(j) *tempColumn.getData(j));
		}
	}


	return tempMatrix;
}

//Multiple wth Vector
Vector Matrix::operator*(const Vector& other) const {
	if (other.getDimensions() == 4) {
		float floats[4] = { 0,0,0,0 };
		const float* temp = other.getData();
		for (int j = 0; j < 4; j++) {
			Vector tempColumn = column(j);
			floats[j] = (temp[0] * tempColumn.getData(0)) + (temp[1] * tempColumn.getData(1)) + (temp[2] * tempColumn.getData(2)) + (temp[3] * tempColumn.getData(3));
		}
		return Vector(floats[0], floats[1], floats[2], floats[3]);
	}
	else return Vector();

}

//Multiple with float
Matrix Matrix::operator*(float c) const {
	Matrix temp;
	for (int i = 0; i < 16; i++) {
		temp.data[i] = this->data[i] * c;
	}
	return temp;
}

/*std::ostream& operator<<(std::ostream& os, const Vector& vector) {
	for (int i = 0; i < 4; i++) {
		os << "<";
		for (int j = 0; j < 4; j++) {
			os << vector.data[(j + (4*i))] << ", ";
		}
		os << ">" << endl;
	}
	return os;
}*/