#pragma once
#include "interfaces/IFullChecksumMatrix.hpp"
#include "RowChecksumMatrix.cpp"
#include "ColumnChecksumMatrix.cpp"
#include <stdlib.h>

template <class T> class FullChecksumMatrix : public virtual Matrix<T>, public IFullChecksumMatrix<T> {
		IRowChecksumMatrix<T>* RCM;
		IColumnChecksumMatrix<T>* CCM;

	public:
		FullChecksumMatrix(IMatrix<T>& M) : Matrix<T>(M.getData(), M.getM() + 1, M.getN() + 1), RCM(new RowChecksumMatrix<T>(M)), CCM(new ColumnChecksumMatrix<T>(*RCM)) {

		}

        ~FullChecksumMatrix() {

        }

        T& operator()(int i, int j) {
            return CCM->operator()(i, j);
        }

        IVector<T>& getRowSummationVector() {
        	return RCM->getRowSummationVector();
        }

        T computeRowSum(int i) {
        	return RCM->computeRowSum(i);
        }

        IVector<T>& getColumnSummationVector() {
        	return CCM->getColumnSummationVector();
        }

        T computeColumnSum(int j) {
        	return CCM->computeColumnSum(j);
        }

        void errorCorrection() {

        }
};
