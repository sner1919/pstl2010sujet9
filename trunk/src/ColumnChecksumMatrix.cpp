#pragma once
#include "IColumnChecksumMatrix.hpp"
#include "Matrix.cpp"
#include "Vector.cpp"
#include "RowChecksumMatrix.cpp"
#include <stdlib.h>

template <class T> class ColumnChecksumMatrix : public ColumnChecksumMatrix<T>, public IColumnChecksumMatrix<T> {
	IVector<T>* columnSummationVector;
	int* corruptedColumns;

	void init() {
		columnSummationVector = new Vector<T>(this->getN());
		corruptedColumns = new int[this->getN()];

		for(int i = 0; i < this->getM(); i++){
			for(int j = 0; j < this->getN() - 1; j++){
				(*columnSummationVector)(j) += (*this)(i, j);
			}
		}
	}

    public:
		ColumnChecksumMatrix(IRowChecksumMatrix<T>& M) : RowChecksumMatrix<T>((IMatrix<T>) M) {
			init();
		}

//		ColumnChecksumMatrix(IMatrix<T>& M) : Matrix<T>(M.getData(), M.getM() + 1, M.getN()) {
//			init();
//		}

		~ColumnChecksumMatrix() {
			delete columnSummationVector;
			delete [] corruptedColumns;
		}

        T& operator()(int i, int j) {
            return i == this->getM() - 1 ? (*columnSummationVector)(j) : this->getData()[i * this->getN() + j];
        }

        IVector<T>& getColumnSummationVector() {
        	return *columnSummationVector;
        }

        int columnErrorDetection(int* corruptedColumns) {
        	T sum;
        	int nb;

        	corruptedColumns = this->corruptedColumns;
        	for(int j = 0; j < this->getN(); j++){
        		sum = 0;
				for(int i = 0; i < this->getM() - 1; i++) sum += (*this)(i, j);
				if((*this)(this->getM() - 1, j) != sum){
					corruptedColumns[nb] = j;
					nb++;
				}
			}

        	return nb;
        }
};

