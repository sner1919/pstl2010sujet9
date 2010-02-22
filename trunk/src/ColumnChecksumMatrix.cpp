#include "Matrix.cpp"
#include "IColumnChecksumMatrix.hpp"

template <class T> class ColumnChecksumMatrix : public Matrix<T>, public IColumnChecksumMatrix<T> {
	T* columnSummationVector;
	int* corruptedColumns;

    public:
		ColumnChecksumMatrix(IMatrix<T>& M) : Matrix<T>(M.getData(), M.getM() + 1, M.getN()) {
			columnSummationVector = new T[M.getN()];
			corruptedColumns = new int[M.getN()];

			for(int j = 0; j < M.getN(); j++){
				for(int i = 0; i < M.getM(); i++){
					columnSummationVector[j] += this->get(i, j);
				}
			}
		}

        T& get(int i, int j){
            return i == this->getM() - 1 ? columnSummationVector[j] : this->getData()[i * (this->getM() - 1) + j];
        }

        void set(int i, int j, T val){
        	(i == this->getM() - 1 ? columnSummationVector[j] : this->getData()[i * (this->getM() - 1) + j]) = val;
        }

        T* getColumnSummationVector(){
        	return columnSummationVector;
        }

        int columnErrorDetection(int* corruptedColumns){
        	T sum;
        	int nb;

        	corruptedColumns = this->corruptedColumns;
        	for(int j = 0; j < this->getN(); j++){
        		sum = 0;
				for(int i = 0; i < this->getM() - 1; i++) sum += this->get(i, j);
				if(get(this->getM() - 1, j) != sum){
					corruptedColumns[nb] = j;
					nb++;
				}
			}

        	return nb;
        }
};

