#pragma once
#include "IRowChecksumMatrix.hpp"
#include "Matrix.cpp"
#include "Vector.cpp"
#include "ColumnChecksumMatrix.cpp"
#include <stdlib.h>

template <class T> class RowChecksumMatrix : public Matrix<T>, public IRowChecksumMatrix<T> {
	IMatrix<T>* M;
	IVector<T>* rowSummationVector;
	int* corruptedRows;

	void init() {
		rowSummationVector = new Vector<T>(this->getM());
		corruptedRows = new int[this->getM()];

		for(int i = 0; i < this->getM(); i++){
			for(int j = 0; j < this->getN() - 1; j++){
				(*rowSummationVector)(i) += (*this)(i, j);
			}
		}
	}

    public:
//		RowChecksumMatrix(IColumnChecksumMatrix<T>& M) : ColumnChecksumMatrix<T>(M) {
//			init();
//		}

		RowChecksumMatrix(IMatrix<T>& M) : Matrix<T>(M.getData(), M.getM(), M.getN() + 1) {
			init();
		}

		~RowChecksumMatrix() {
			delete rowSummationVector;
			delete [] corruptedRows;
		}

        T& operator()(int i, int j) {
            return j == this->getN() - 1 ? (*rowSummationVector)(i) : this->getData()[i * (this->getN() - 1) + j];
        }

        IVector<T>& getRowSummationVector() {
        	return *rowSummationVector;
        }

        int rowErrorDetection(int* corruptedRows) {
        	T sum;
        	int nb;

        	corruptedRows = this->corruptedRows;
        	for(int i = 0; i < this->getM(); i++){
        		sum = 0;
				for(int j = 0; j < this->getN() - 1; j++) sum += (*this)(i, j);
				if((*this)(i, this->getN() - 1) != sum){
					corruptedRows[nb] = i;
					nb++;
				}
			}

        	return nb;
        }
};

