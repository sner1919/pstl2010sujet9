#include "Matrix.hpp"
#include <sstream>
#include <stdexcept>
#include <cmath>

template <class T>
Matrix<T>::Matrix(const Matrix<T>& M) : m(M.getM()), n(M.getN()), dataAllocation(M.getDataAllocation()) {
	if(dataAllocation){
		data = new T[m * n];
		for(int i = 0; i < m * n; i++) data[i] = 0.;
		copy(M.getData(), M.getData() + m * n, data);
	}else{
		data = M.getData();
	}
}

template <class T>
Matrix<T>::Matrix(int m, int n) : m(m), n(n), data(new T[m * n]), dataAllocation(true) {
	for(int i = 0; i < m * n; i++) data[i] = 0;
}

template <class T>
Matrix<T>::Matrix(T* data, int m, int n) : m(m), n(n), data(data), dataAllocation(false) {}

template <class T>
Matrix<T>::~Matrix() {
	if(dataAllocation) delete [] data;
}

template <class T>
int Matrix<T>::getM() const {
	return m;
}

template <class T>
int Matrix<T>::getN() const {
	return n;
}

template <class T>
T* Matrix<T>::getData() const {
	return data;
}

template <class T>
bool Matrix<T>::getDataAllocation() const {
	return dataAllocation;
}

template <class T>
TYPE_UNION Matrix<T>::operator()(int i, int j) const {
	TYPE_UNION v(data[(i - 1) * getN() + (j - 1)]);
	return v;
}

template <class T>
IMatrix<T>& Matrix<T>::operator=(const IMatrix<T>& M) {
	// Vérifications
	if(getM() != M.getM() || getN() != M.getN()) throw domain_error("affectation impossible");

	for(int i = 1; i <= getM(); i++){
		for(int j = 1; j <= getN(); j++) (*this)(i, j) = M(i, j);
	}

	return *this;
}

template <class T>
bool Matrix<T>::operator==(const IMatrix<T>& M) const {
	if(getM() != M.getM() || getN() != M.getN()) return false;

	return distance(M) == 0;
}

template <class T>
string Matrix<T>::toString() const {
	ostringstream oss;

	oss.precision(STREAM_PRECISION);
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
int Matrix<T>::locationId(int i, int j) const {
	return (i - 1) * getN() + j;
}

template <class T>
int Matrix<T>::distance(const IMatrix<T>& M) const {
	// Vérifications
	if(getM() != M.getM() || getN() != M.getN()) throw domain_error("calcul de la distance impossible");

	int n = 0;

	for(int i = 1; i <= getM(); i++){
		for(int j = 1; j <= getN(); j++){
			if(!equal((*this)(i, j).toDouble(), M(i, j).toDouble(), EPS1, EPS0)) n++;
		}
	}

	return n;
}

template <class T>
int Matrix<T>::weight() const {
	int n = 0;

	for(int i = 1; i <= getM(); i++){
		for(int j = 1; j <= getN(); j++){
			if((*this)(i, j) != 0) n++;
		}
	}

	return n;
}

template <class T>
void Matrix<T>::fromDouble(double* t, bool rowMajor) {
	for(int i = 1; i <= getM(); i++){
		for(int j = 1; j <= getN(); j++){
			(*this)(i, j) = t[(rowMajor ? (i - 1) * getN() + (j - 1) : (j - 1) * getM() + (i - 1))];
		}
	}
}

template <class T>
void Matrix<T>::toDouble(double* t, bool rowMajor) const {
	for(int i = 1; i <= getM(); i++){
		for(int j = 1; j <= getN(); j++){
			t[(rowMajor ? (i - 1) * getN() + (j - 1) : (j - 1) * getM() + (i - 1))] = (*this)(i, j).toDouble();
		}
	}
}

template class Matrix<double>;
template class Matrix<TYPE_SUM>;
