#include "RowChecksumMatrix.hpp"

template <class T>
RowChecksumMatrix<T>::RowChecksumMatrix(IMatrix<T>& M) : Matrix<T>(M.getData(), M.getM(), M.getN() + 1), M(M) {
	rowSummationVector = new Vector<T>(this->getM());

	for(int i = 1; i <= this->getM(); i++) (*rowSummationVector)(i) = computeRowSum(i);
}

template <class T>
RowChecksumMatrix<T>::~RowChecksumMatrix() {
	delete (Vector<T>*) rowSummationVector;
}

template <class T>
T& RowChecksumMatrix<T>::operator()(int i, int j) {
	return j == this->getN() ? (*rowSummationVector)(i) : M(i, j);
}

template <class T>
IVector<T>& RowChecksumMatrix<T>::getRowSummationVector() {
	return *rowSummationVector;
}

template <class T>
T RowChecksumMatrix<T>::computeRowSum(int i) {
	T sum;

	for(int j = 1; j < this->getN(); j++) sum += (*this)(i, j);

	return sum;
}

template class RowChecksumMatrix<double>;
