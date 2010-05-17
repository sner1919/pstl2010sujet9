#include "RowChecksumMatrix.hpp"

template <class T>
RowChecksumMatrix<T>::RowChecksumMatrix(RowChecksumMatrix<T>& RCM) :
Matrix<T>(RCM.getData(), RCM.getM(), RCM.getN()),
matrix(RCM.getRowMatrix()),
rowSummationVector(RCM.getRowSummationVector()) {}

template <class T>
RowChecksumMatrix<T>::RowChecksumMatrix(IMatrix<T>& M) :
Matrix<T>(M.getData(), M.getM(), M.getN() + 1),
matrix(M),
rowSummationVector(*(new Vector<PSTL_TYPE_SUM>(this->getM(), false))) {
	for(int i = 1; i <= this->getM(); i++) {
		rowSummationVector(i) = 0;
		rowSummationVector(i) = computeRowSum(i);
	}
}

template <class T>
RowChecksumMatrix<T>::~RowChecksumMatrix() {
	delete dynamic_cast<Vector<T>*>(&rowSummationVector);
}

template <class T>
PSTL_TYPE_UNION RowChecksumMatrix<T>::operator()(int i, int j) const {
	return j == this->getN() ? rowSummationVector(i) : matrix(i, j);
}

template <class T>
IMatrix<T>& RowChecksumMatrix<T>::getRowMatrix() const {
	return matrix;
}

template <class T>
IVector<PSTL_TYPE_SUM>& RowChecksumMatrix<T>::getRowSummationVector() const {
	return rowSummationVector;
}

template <class T>
PSTL_TYPE_SUM RowChecksumMatrix<T>::computeRowSum(int i) const {
	PSTL_TYPE_SUM sum = 0;

	for(int j = 1; j < this->getN(); j++) sum += (*this)(i, j);

	return sum - (*this)(i, this->getN());
}

template <class T>
bool RowChecksumMatrix<T>::rowErrorDetection() const {
	for(int i = 1; i <= this->getM(); i++) if(computeRowSum(i) != 0) return true;

	return false;
}

template class RowChecksumMatrix<double>;
