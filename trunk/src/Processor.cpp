#include "ICalculator.hpp"

template <class T> class Processor : public ICalculator<T> {
		ICalculator<T>* calculator;
    
    public:
		Processor(ICalculator<T>* calculator){
			this->calculator = calculator;
		}

		void mult(IMatrix<T>& Res,IMatrix<T>& A, IMatrix<T>& B){
			this->calculator->mult(Res, A, B);
		}

		void mult(IMatrix<T>& Res,IMatrix<T>& A, T x){
			this->calculator->mult(Res, A, x);
		}

		void add(IMatrix<T>& Res,IMatrix<T>& A, IMatrix<T>& B){
			this->calculator->add(Res, A, B);
		}

		void transpose(IMatrix<T>& Res, IMatrix<T>& A){
			this->calculator->transpose(Res, A);
		}

		void LU(IMatrix<T>& L, IMatrix<T>& U, IMatrix<T>& A){
			this->calculator->LU(L, U, A);
		}
};


