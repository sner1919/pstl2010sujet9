#include "IRowChecksumMatrix.hpp"
#include "Matrix.cpp"
#include "Vector.cpp"
#include <stdlib.h>

template <class T> class RowChecksumMatrix : public IRowChecksumMatrix<T> {
	IMatrix<T>* M;
	IVector<T>* rowSummationVector;
	int* corruptedRows;

    public:
		RowChecksumMatrix(IMatrix<T>& M) {
			this->M = &M;
			rowSummationVector = new Vector<T>(M.getM());
			corruptedRows = new int[M.getM()];

			for(int i = 0; i < M.getM(); i++){
				for(int j = 0; j < M.getN(); j++){
					(*rowSummationVector)(i) += M(i, j);
				}
			}
		}

		~RowChecksumMatrix(){
			delete rowSummationVector;
			delete [] corruptedRows;
		}

        int getM(){
            return M->getM();
        }

        int getN(){
            return M->getN() + 1;
        }

        T* getData(){
            return M->getData();
        }

        T& operator()(int i, int j){
            return j == M->getN() ? (*rowSummationVector)(i) : (*M)(i, j);
        }

        string toString() {
            ostringstream oss;

            oss << "[" << endl;
            for(int i = 0; i < getM(); i++){
                for(int j = 0; j < getN(); j++){
                    oss << (*this)(i, j) << " ";
                }
                oss << endl;
            }
            oss << "]" << endl;

            return oss.str();
        }

		IVector<T>& getRowSummationVector(){
        	return *rowSummationVector;
        }

        int rowErrorDetection(int* corruptedRows){
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

