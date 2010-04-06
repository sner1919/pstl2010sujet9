#include "ColumnChecksumMatrix.hpp"

template <class T>
ColumnChecksumMatrix<T>::ColumnChecksumMatrix(const IColumnChecksumMatrix<T>& M) : Matrix<T>(M), columnSummationVector(new Vector<T>(this->getN())) {}

template <class T>
ColumnChecksumMatrix<T>::ColumnChecksumMatrix(IMatrix<T>& M) : Matrix<T>(M, M.getM() + 1, M.getN()), columnSummationVector(new Vector<T>(this->getN())) {
	for(int j = 1; j <= this->getN(); j++) (*columnSummationVector)(j) = computeColumnSum(j);
}

template <class T>
ColumnChecksumMatrix<T>::~ColumnChecksumMatrix() {
	delete (Vector<T>*) columnSummationVector;
}

template <class T>
T& ColumnChecksumMatrix<T>::operator()(int i, int j) const {
	return i == this->getM() ? (*columnSummationVector)(j) : Matrix<T>::operator()(i, j);
}

template <class T>
IVector<T>& ColumnChecksumMatrix<T>::getColumnSummationVector() const {
	return *columnSummationVector;
}

template <class T>
T ColumnChecksumMatrix<T>::computeColumnSum(int j) const {
	T sum = 0;

	for(int i = 1; i < this->getM(); i++) sum += (*this)(i, j);

	return sum - (*this)(this->getM(), j);
}

template class ColumnChecksumMatrix<PSTL_TYPE>;
