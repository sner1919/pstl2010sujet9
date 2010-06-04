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
rowSummationVector(*(new Vector<double>(this->getM(), false))),
dataAllocation(true) {
	for(int i = 1; i <= this->getM(); i++) {
		rowSummationVector(i) = 0;
		rowSummationVector(i) = computeRowSum(i);
	}
}

template <class T>
RowChecksumMatrix<T>::~RowChecksumMatrix() {
	if(dataAllocation) delete dynamic_cast<Vector<double>*>(&rowSummationVector);
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
IVector<double>& RowChecksumMatrix<T>::getRowSummationVector() const {
	return rowSummationVector;
}

template <class T>
double RowChecksumMatrix<T>::computeRowSum(int i) const {
	double sum = 0;

	for(int j = 1; j < this->getN(); j++) sum += (*this)(i, j).toDouble();

	return sum - (*this)(i, this->getN()).toDouble();
}

template <class T>
bool RowChecksumMatrix<T>::rowErrorDetection(int i) const {
	double sum = 0;

	for(int j = 1; j < this->getN(); j++) sum += (*this)(i, j).toDouble();

	return !equal(sum, (*this)(i, this->getN()).toDouble(), EPS1, EPS0);
}

template <class T>
bool RowChecksumMatrix<T>::rowErrorDetection() const {
	for(int i = 1; i <= this->getM(); i++) if(rowErrorDetection(i)) return true;

	return false;
}

template class RowChecksumMatrix<double>;
