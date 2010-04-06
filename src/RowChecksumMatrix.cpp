#include "RowChecksumMatrix.hpp"

template <class T>
RowChecksumMatrix<T>::RowChecksumMatrix(const IRowChecksumMatrix<T>& M) : Matrix<T>(M), rowSummationVector(new Vector<T>(this->getM())) {}

template <class T>
RowChecksumMatrix<T>::RowChecksumMatrix(IMatrix<T>& M) : Matrix<T>(M, M.getM(), M.getN() + 1), rowSummationVector(new Vector<T>(this->getM())) {
	for(int i = 1; i <= this->getM(); i++) (*rowSummationVector)(i) = computeRowSum(i);
}

template <class T>
RowChecksumMatrix<T>::~RowChecksumMatrix() {
	delete (Vector<T>*) rowSummationVector;
}

template <class T>
T& RowChecksumMatrix<T>::operator()(int i, int j) const {
	return j == this->getN() ? (*rowSummationVector)(i) : Matrix<T>::operator()(i, j);
}

template <class T>
IVector<T>& RowChecksumMatrix<T>::getRowSummationVector() const {
	return *rowSummationVector;
}

template <class T>
T RowChecksumMatrix<T>::computeRowSum(int i) const {
	T sum = 0;

	for(int j = 1; j < this->getN(); j++) sum += (*this)(i, j);

	return sum - (*this)(i, this->getN());
}

template class RowChecksumMatrix<PSTL_TYPE>;
