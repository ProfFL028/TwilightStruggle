#include "Matrix.h"


Matrix::Matrix()
{
}

Matrix::Matrix(char* data, int w, int h) {

}


bool Matrix::setData(char* data, int w, int h) {
	values = new float*[w];
	
	return false;
}




Matrix::~Matrix()
{
	delete values;
}
