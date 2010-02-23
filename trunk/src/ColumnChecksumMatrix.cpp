#pragma once
#include "IColumnChecksumMatrix.hpp"
#include "Matrix.cpp"
#include "Vector.cpp"
#include <stdlib.h>

template <class T> class ColumnChecksumMatrix : public virtual Matrix<T>, public virtual IColumnChecksumMatrix<T> {
	IMatrix<T>& M;
	IVector<T>* columnSummationVector;

	public:
		ColumnChecksumMatrix(IMatrix<T>& M) : Matrix<T>(M.getData(), M.getM() + 1, M.getN()), M(M) {
			columnSummationVector = new Vector<T>(this->getN());

			for(int i = 1; i < this->getM(); i++){
				for(int j = 1; j <= this->getN(); j++){
					(*columnSummationVector)(j) += (*this)(i, j);
				}
			}
		}

		~ColumnChecksumMatrix() {
			delete columnSummationVector;
		}

        T& operator()(int i, int j) {
            return i == this->getM() ? (*columnSummationVector)(j) : M(i, j);
        }

        IVector<T>& getColumnSummationVector() {
        	return *columnSummationVector;
        }

        int columnErrorDetection(int* corruptedColumns) {
        	T sum;
        	int nb;

			corruptedColumns = new int[this->getN()];
        	for(int j = 1; j <= this->getN(); j++){
        		sum = 0;
				for(int i = 1; i < this->getM(); i++) sum += (*this)(i, j);
				if((*this)(this->getM(), j) != sum){
					corruptedColumns[nb] = j;
					nb++;
				}
			}

        	return nb;
        }
};

