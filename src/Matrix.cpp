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
	for(int i = 1; i <= getM(); i++){
		for(int j = 1; j <= getN(); j++){
			if((*this)(i, j) != M(i, j)) return false;
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

template class Matrix<double>;
