#pragma once
#include "settings.hpp"
#include "CalculatorNaive.hpp"
#include "interfaces/IBlasLapackAdapter.hpp"

template <class T> class CalculatorBlasLapack : public CalculatorNaive<T> {
		IBlasLapackAdapter& blasLapackAdapter;
		int MatrixType;

	public:
		/*
		 * Crée un calculateur utilisant l'interface Blas et Lapack.
		 * @param blasLapackAdapter l'adaptateur vers une implémentation de l'interface Blas et Lapack
		 * @param MatrixType indique le type des matrices utilisé :
		 *     0 : matrices quelconque (utilisation de toDouble() et fromDouble())
		 *     1 : matrices de doubles (utilisation de getData())
		 */
		CalculatorBlasLapack(IBlasLapackAdapter& blasLapackAdapter, int MatrixType);

		// implémentation de ICalculator<T>
		void mult(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const;

		// implémentation de ICalculator<T>
		void mult(IMatrix<T>& Res, const IMatrix<T>& A, T x) const;

		// implémentation de ICalculator<T>
		void add(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const;

		// implémentation de ICalculator<T>
		void LU(IMatrix<T>& P, IMatrix<T>& L, IMatrix<T>& U, const IMatrix<T>& A) const;
};
