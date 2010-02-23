#pragma once
#include "IRowChecksumMatrix.hpp"
#include "Matrix.cpp"
#include "Vector.cpp"
#include <stdlib.h>

template <class T> class RowChecksumMatrix : public virtual Matrix<T>, public virtual IRowChecksumMatrix<T> {
	IMatrix<T>& M;
	IVector<T>* rowSummationVector;

	public:
		RowChecksumMatrix(IMatrix<T>& M) : Matrix<T>(M.getData(), M.getM(), M.getN() + 1), M(M) {
			rowSummationVector = new Vector<T>(this->getM());

			for(int i = 1; i <= this->getM(); i++){
				for(int j = 1; j < this->getN(); j++){
					(*rowSummationVector)(i) += (*this)(i, j);
				}
			}
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

        int rowErrorDetection(int* corruptedRows) {
        	T sum;
        	int nb;

        	corruptedRows = new int[this->getM()];
        	for(int i = 1; i <= this->getM(); i++){
        		sum = 0;
				for(int j = 1; j < this->getN(); j++) sum += (*this)(i, j);
				if((*this)(i, this->getN()) != sum){
					corruptedRows[nb] = i;
					nb++;
				}
			}

        	return nb;
        }
};

