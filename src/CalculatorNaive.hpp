#pragma once
#include "settings.hpp"
#include "interfaces/ICalculator.hpp"
#include <cmath>

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
		void LU(IMatrix<T>& P, IMatrix<T>& L, IMatrix<T>& U, const IMatrix<T>& A) const;
};

// permet de faire des opérations avec des types différents
template <class T1, class T2, class T3> void CalculatorNaiveMult(IMatrix<T1>& Res, const IMatrix<T2>& A, const IMatrix<T3>& B);
template <class T1, class T2, class T3> void CalculatorNaiveMult(IMatrix<T1>& Res, const IMatrix<T2>& A, T3 x);
template <class T1, class T2, class T3> void CalculatorNaiveAdd(IMatrix<T1>& Res, const IMatrix<T2>& A, const IMatrix<T3>& B);
template <class T1, class T2, class T3> void CalculatorNaiveTranspose(IMatrix<T1>& Res, const IMatrix<T2>& A);
template <class T1, class T2, class T3, class T4> void CalculatorNaiveLU(IMatrix<T1>& P, IMatrix<T2>& L, IMatrix<T3>& U, const IMatrix<T4>& A);
template <class T1, class T2> void CalculatorNaiveAddBlock(IMatrix<T1>& Res, const IMatrix<T2>& A, int x, int y, int i, int j, int N);
template <class T1, class T2> void CalculatorNaiveSubBlock(IMatrix<T1>& Res, const IMatrix<T2>& A, int x, int y, int i, int j, int N);
template <class T1, class T2> void CalculatorNaiveCopyBlock(IMatrix<T1>& Res, const IMatrix<T2>& A, int x, int y, int N);
template <class T1, class T2, class T3> void CalculatorNaiveMult2(IMatrix<T1>& Res, const IMatrix<T2>& A, const IMatrix<T3>& B);
template <class T1, class T2, class T3> void Strassen(IMatrix<T1>& Res, const IMatrix<T2>& A, const IMatrix<T3>& B, int N);
