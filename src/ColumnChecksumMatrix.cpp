#include "ColumnChecksumMatrix.hpp"
#include "Vector.hpp"

template <class T>
ColumnChecksumMatrix<T>::ColumnChecksumMatrix(IMatrix<T>& M) :
Matrix<T>(M.getData(), M.getM() + 1, M.getN()),
matrix(M),
columnSummationVector(*(new Vector<TYPE_SUM>(this->getN(), true))) {
	for(int j = 1; j <= this->getN(); j++) {
		columnSummationVector(j) = 0;
		columnSummationVector(j) = computeColumnSum(j);
	}
}

template <class T>
ColumnChecksumMatrix<T>::~ColumnChecksumMatrix() {
	delete dynamic_cast<Vector<TYPE_SUM>*>(&columnSummationVector);
}

template <class T>
PSTL_TYPE_UNION ColumnChecksumMatrix<T>::operator()(int i, int j) const {
	return i == this->getM() ? columnSummationVector(j) : matrix(i, j);
}

template <class T>
IMatrix<T>& ColumnChecksumMatrix<T>::getColumnMatrix() const {
	return matrix;
}

template <class T>
IVector<TYPE_SUM>& ColumnChecksumMatrix<T>::getColumnSummationVector() const {
	return columnSummationVector;
}

template <class T>
TYPE_SUM ColumnChecksumMatrix<T>::computeColumnSum(int j) const {
	TYPE_SUM sum = 0;

	for(int i = 1; i < this->getM(); i++) sum += (*this)(i, j).toTypeSum();

	return sum - (*this)(this->getM(), j).toTypeSum();
}

template <class T>
bool ColumnChecksumMatrix<T>::columnErrorDetection() const {
	for(int j = 1; j <= this->getN(); j++) if(!equal(TYPE_SUM_TO_DOUBLE(computeColumnSum(j)), 0., EPS1, 0)) return true;

	return false;
}

template class ColumnChecksumMatrix<double>;
