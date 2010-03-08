#pragma once
#include "interfaces/IFullChecksumMatrix.hpp"
#include "RowChecksumMatrix.cpp"
#include "ColumnChecksumMatrix.cpp"
#include <stdlib.h>
#include <vector>
using std::vector;

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
        	IVector<T> *rowVector = &getRowSummationVector();
        	IVector<T> *colVector = &getColumnSummationVector();
        	vector<int> erreurlignes;
        	vector<int> erreurcolonnes;
        	if((computeRowSum(this.getM() != colVector->operator ()(this.getN())))
        	        		|| (computeColumnSum(this.getN() != colVector->operator ()(this.getN())))){

        	        	}
        	for(int i = 0; i < this.getM()-1;i++)
        	{
        		if(computeRowSum(i) != rowVector->operator ()(i)){
        			if((computeColumnSum(this.getN() != colVector->operator ()(this.getN()))))
        			{
        				rowVector->operator ()(i) = computeRowSum(i);
        			}
        			else{
        				erreurlignes.push_back(i);
        			}
        		}
        	}
        	for(int j = 0; j < this.getN()-1;j++)
        	{
          		if(computeColumnSum(j) != colVector->operator ()(i)){
        	        if((computeRowSum(this.getM() != colVector->operator ()(this.getN()))))
        	        {
        	        	colVector->operator ()(i) = computeColumnSum(i);
        	        }
        	        else{
        	        	erreurcolonnes.push_back(i);
        	       	}
        	    }
        	}
        	if(erreurlignes.size() == 1){
        		(*this)(erreurlignes[0],erreurscolonnes[0]) +=
        				computeColumnSum(erreurscolonnes[0]) - colVector -> operator ()(erreurscolonnes[0]);
        	}
        }
};
