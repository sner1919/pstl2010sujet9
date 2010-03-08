#pragma once
#include "interfaces/IRowChecksumMatrix.hpp"
#include "Matrix.cpp"
#include "Vector.hpp"
#include <stdlib.h>

template <class T> class RowChecksumMatrix : public virtual Matrix<T>, public virtual IRowChecksumMatrix<T> {
		IMatrix<T>& M;
		IVector<T>* rowSummationVector;

	public:
		RowChecksumMatrix(IMatrix<T>& M) : Matrix<T>(M.getData(), M.getM(), M.getN() + 1), M(M) {
			rowSummationVector = new Vector<T>(this->getM());

			for(int i = 1; i <= this->getM(); i++) (*rowSummationVector)(i) = computeRowSum(i);
		}

		~RowChecksumMatrix() {
			delete rowSummationVector;
		}

        T& operator()(int i, int j) {
            return j == this->getN() ? (*rowSummationVector)(i) : M(i, j);
        }

        IVector<T>& getRowSummationVector() {
        	return *rowSummationVector;
        }

        T computeRowSum(int i) {
        	T sum;

        	for(int j = 1; j < this->getN(); j++) sum += (*this)(i, j);

        	return sum;
        }
};

