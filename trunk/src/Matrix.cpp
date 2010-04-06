#include "Matrix.hpp"

template <class T>
Matrix<T>::Matrix(IMatrix<T>& M, int m, int n) {
	this->M = &M;
	this->m = m;
	this->n = n;
	dataAllocation = false;
	if(data) cout << "coucou";
	else cout << "tata";
}

template <class T>
Matrix<T>::Matrix(const IMatrix<T>& M) {
	Matrix<T>::Matrix(M.getM(), M.getN());
	*this = M;
}

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
int Matrix<T>::getM() const {
	return m;
}

template <class T>
int Matrix<T>::getN() const {
	return n;
}

template <class T>
T* Matrix<T>::getData() const {
	return data ? data : M->getData();
}

template <class T>
T& Matrix<T>::operator()(int i, int j) const {
	return data ? data[(i - 1) * n + (j - 1)] : (*M)(i, j);
}

template <class T>
IMatrix<T>& Matrix<T>::operator=(const IMatrix<T>& M) {
	// Vérifications
	if(getM() != M.getM() || getN() != M.getN()) throw domain_error("affectation impossible");

	// si on fait ça on ne peut pas réutiliser cette methode avec les RCM, CCM et FCM
	// copy(M.getData(), M.getData() + M.getM() * M.getN(), data);

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
			if((*this)(i, j) != M(i, j)) n++;
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

template class Matrix<PSTL_TYPE>;
