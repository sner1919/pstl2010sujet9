#include "RowChecksumMatrix.hpp"
#include "Vector.hpp"

template <class T>
RowChecksumMatrix<T>::RowChecksumMatrix(RowChecksumMatrix<T>& RCM) :
Matrix<T>(RCM.getData(), RCM.getM(), RCM.getN()),
matrix(RCM.getRowMatrix()),
rowSummationVector(RCM.getRowSummationVector()),
dataAllocation(false) {}

template <class T>
RowChecksumMatrix<T>::RowChecksumMatrix(IMatrix<T>& M) :
Matrix<T>(M.getData(), M.getM(), M.getN() + 1),
matrix(M),
rowSummationVector(*(new Vector<TYPE_SUM>(this->getM(), false))),
dataAllocation(true) {
	for(int i = 1; i <= this->getM(); i++) {
		rowSummationVector(i) = 0;
		rowSummationVector(i) = computeRowSum(i);
	}
}

template <class T>
RowChecksumMatrix<T>::~RowChecksumMatrix() {
	if(dataAllocation) delete dynamic_cast<Vector<TYPE_SUM>*>(&rowSummationVector);
}

template <class T>
TYPE_UNION RowChecksumMatrix<T>::operator()(int i, int j) const {
	return j == this->getN() ? rowSummationVector(i) : matrix(i, j);
}

template <class T>
IMatrix<T>& RowChecksumMatrix<T>::getRowMatrix() const {
	return matrix;
}

template <class T>
IVector<TYPE_SUM>& RowChecksumMatrix<T>::getRowSummationVector() const {
	return rowSummationVector;
}

template <class T>
TYPE_SUM RowChecksumMatrix<T>::computeRowSum(int i) const {
	TYPE_SUM sum = 0;

	for(int j = 1; j < this->getN(); j++) sum += (*this)(i, j).toTypeSum();

	return sum - (*this)(i, this->getN()).toTypeSum();
}

template <class T>
bool RowChecksumMatrix<T>::rowErrorDetection(int i) const {
	TYPE_SUM sum = 0;

	for(int j = 1; j < this->getN(); j++) sum += (*this)(i, j).toTypeSum();

	return !equal(TYPE_SUM_TO_DOUBLE(sum), (*this)(i, this->getN()).toDouble(), EPS1, EPS0);
}

template <class T>
bool RowChecksumMatrix<T>::rowErrorDetection() const {
	for(int i = 1; i <= this->getM(); i++) if(rowErrorDetection(i)) return true;

	return false;
}

template class RowChecksumMatrix<double>;
