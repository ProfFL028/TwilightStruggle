#pragma once

#include <iostream>

class Matrix
{
public:
	Matrix();
	Matrix(char* data, int w, int h);
	~Matrix();

	bool setData(char* data, int w, int h);

protected:
	float** values;
	int width, height;
};

