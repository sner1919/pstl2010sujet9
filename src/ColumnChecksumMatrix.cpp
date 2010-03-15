#include "ColumnChecksumMatrix.hpp"

template <class T>
ColumnChecksumMatrix<T>::ColumnChecksumMatrix(IMatrix<T>& M) : Matrix<T>(M.getData(), M.getM() + 1, M.getN()), M(M) {
	columnSummationVector = new Vector<T>(this->getN());

	for(int j = 1; j <= this->getN(); j++){
		(*columnSummationVector)(j) = 0;
		(*columnSummationVector)(j) = computeColumnSum(j);
	}
}

template <class T>
ColumnChecksumMatrix<T>::~ColumnChecksumMatrix() {
	delete (Vector<T>*) columnSummationVector;
}

template <class T>
T& ColumnChecksumMatrix<T>::operator()(int i, int j) {
	return i == this->getM() ? (*columnSummationVector)(j) : M(i, j);
}

template <class T>
IVector<T>& ColumnChecksumMatrix<T>::getColumnSummationVector() {
	return *columnSummationVector;
}

template <class T>
T ColumnChecksumMatrix<T>::computeColumnSum(int j) {
	T sum = 0;

	for(int i = 1; i < this->getM(); i++) sum += (*this)(i, j);

	return sum - (*this)(this->getM(), j);
}

template class ColumnChecksumMatrix<double>;
