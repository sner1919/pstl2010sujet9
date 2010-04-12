#include "ColumnChecksumMatrix.hpp"

template <class T>
ColumnChecksumMatrix<T>::ColumnChecksumMatrix(IMatrix<T>& M) :
Matrix<T>(M.getData(), M.getM() + 1, M.getN()),
matrix(M),
columnSummationVector(*(new Vector<T>(this->getN()))) {
	for(int j = 1; j <= this->getN(); j++) {
		columnSummationVector(j) = 0;
		columnSummationVector(j) = computeColumnSum(j);
	}
}

template <class T>
ColumnChecksumMatrix<T>::~ColumnChecksumMatrix() {
	delete dynamic_cast<Vector<T>*>(&columnSummationVector);
}

template <class T>
T& ColumnChecksumMatrix<T>::operator()(int i, int j) const {
	return i == this->getM() ? columnSummationVector(j) : matrix(i, j);
}

template <class T>
IMatrix<T>& ColumnChecksumMatrix<T>::getColumnMatrix() const {
	return matrix;
}

template <class T>
IVector<T>& ColumnChecksumMatrix<T>::getColumnSummationVector() const {
	return columnSummationVector;
}

template <class T>
T ColumnChecksumMatrix<T>::computeColumnSum(int j) const {
	T sum = 0;

	for(int i = 1; i < this->getM(); i++) sum += (*this)(i, j);

	return sum - (*this)(this->getM(), j);
}

template <class T>
bool ColumnChecksumMatrix<T>::columnErrorDetection() const {
	for(int j = 1; j <= this->getN(); j++) if(computeColumnSum(j) != 0) return true;

	return false;
}

template class ColumnChecksumMatrix<PSTL_TYPE>;
