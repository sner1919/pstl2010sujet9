#pragma once
#include "IFullChecksumMatrix.hpp"
#include "ColumnChecksumMatrix.cpp"
#include "RowChecksumMatrix.cpp"
#include "Vector.cpp"
#include <stdlib.h>

template <class T> class FullChecksumMatrix : public RowChecksumMatrix<T>, public ColumnChecksumMatrix<T>, public IFullChecksumMatrix<T> {
	public:
		FullChecksumMatrix(IMatrix<T>& M) : Matrix<T>(M.getData(), M.getM() + 1, M.getN() + 1), RowChecksumMatrix<T>(M), ColumnChecksumMatrix<T>((*this)) {

		}

        T& operator()(int i, int j) {
            return ColumnChecksumMatrix<T>::operator()(i, j);
        }
};
