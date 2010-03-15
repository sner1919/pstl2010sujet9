#include "interfaces/ICalculator.hpp"
#include <stdexcept>
#include <cblas.h>
#include "clapack.h"


template <class T> class Calculator2 : public ICalculator<T> {
		int* ipvt;
		int info;

	public:
		// implémentation de ICalculator<T>
		void mult(IMatrix<T>& Res, IMatrix<T>& A, IMatrix<T>& B);

		// implémentation de ICalculator<T>
		void mult(IMatrix<T>& Res,IMatrix<T>& A, T x);

		// implémentation de ICalculator<T>
		void add(IMatrix<T>& Res,IMatrix<T>& A, IMatrix<T>& B);

		// implémentation de ICalculator<T>
		void transpose(IMatrix<T>& Res, IMatrix<T>& A);

		// implémentation de ICalculator<T>
		void LU(IMatrix<T>& L, IMatrix<T>& U, IMatrix<T>& A);
};
