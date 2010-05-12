#include "interfaces/ICalculator.hpp"
#include "CalculatorNaive.hpp"
#include <stdexcept>
#include <cblas.h>
#include "clapack.h"

template <class T> class CalculatorAtlas : public CalculatorNaive<T>, public virtual ICalculator<T> {
	public:
		// implémentation de ICalculator<T>
		void mult(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const;

		// implémentation de ICalculator<T>
		void LU(IMatrix<T>& L, IMatrix<T>& U, const IMatrix<T>& A) const;
};
