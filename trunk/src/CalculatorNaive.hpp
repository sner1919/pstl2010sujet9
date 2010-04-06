#pragma once
#include "interfaces/ICalculator.hpp"
#include <stdexcept>

template <class T> class CalculatorNaive : public virtual ICalculator<T> {
	public:
		// implémentation de ICalculator<T>
		void mult(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const;

		// implémentation de ICalculator<T>
		void mult(IMatrix<T>& Res, const IMatrix<T>& A, T x) const;

		// implémentation de ICalculator<T>
		void add(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const;

		// implémentation de ICalculator<T>
		void transpose(IMatrix<T>& Res, const IMatrix<T>& A) const;

		// implémentation de ICalculator<T>
		void LU(IMatrix<T>& L, IMatrix<T>& U, const IMatrix<T>& A) const;
};
