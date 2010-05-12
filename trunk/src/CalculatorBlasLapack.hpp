#include "interfaces/ICalculator.hpp"
#include "interfaces/IBlasLapackAdapter.hpp"
#include <stdexcept>

template <class T> class CalculatorBlasLapack : public virtual ICalculator<T> {
		IBlasLapackAdapter& blasLapackAdapter;

	public:
		/*
		 * Crée un calculateur utilisant l'interface Blas et Lapack.
		 * @param blasLapackAdapter l'adaptateur vers une implémentation de l'interface Blas et Lapack
		 */
		CalculatorBlasLapack(IBlasLapackAdapter& blasLapackAdapter);

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
