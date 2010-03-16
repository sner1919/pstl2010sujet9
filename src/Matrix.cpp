#include "Matrix.hpp"

template <class T>
Matrix<T>::Matrix(int m, int n) {
	this->data = new T[m * n];
	this->m = m;
	this->n = n;
	dataAllocation = true;
}

template <class T>
Matrix<T>::Matrix(T* data, int m, int n) {
	this->data = data;
	this->m = m;
	this->n = n;
	dataAllocation = false;
}

template <class T>
Matrix<T>::~Matrix() {
	if(dataAllocation) delete [] data;
}

template <class T>
int Matrix<T>::getM() {
	return m;
}

template <class T>
int Matrix<T>::getN() {
	return n;
}

template <class T>
T* Matrix<T>::getData() {
	return data;
}

template <class T>
T& Matrix<T>::operator()(int i, int j) {
	return data[(i - 1) * n + (j - 1)];
}

template <class T>
bool Matrix<T>::operator==(IMatrix<T>& M) {
	if(getM() != M.getM() || getN() != M.getN()) return false;

	for(int i = 1; i <= getM(); i++){
		for(int j = 1; j <= getN(); j++){
			T a = (*this)(i, j);
			T b = M(i, j);
			if(fabs(a - b) > 1){
				printf("a : %lf\n", a);
				printf("b : %lf\n", b);
				cout << fabs(a - b) << endl;
				cout << (*this)(i, j) << " != " << M(i, j) << endl;
				return false;
			}
		}
	}

	return true;
}

template <class T>
string Matrix<T>::toString() {
	ostringstream oss;

	oss << "[" << endl;
	for(int i = 1; i <= getM(); i++){
		for(int j = 1; j <= getN(); j++){
			oss << (*this)(i, j) << " ";
		}
		oss << endl;
	}
	oss << "]" << endl;

	return oss.str();
}

template <class T>
int Matrix<T>::locationId(int i, int j) {
	return (i - 1) * getN() + j;
}

template class Matrix<double>;
