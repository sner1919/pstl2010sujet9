#include "interfaces/ICalculator.hpp"
#include "FullChecksumMatrix.hpp"
#include "ErrorGenerator.hpp"

template <class T> class Processor : public ICalculator<T> {
		ICalculator<T>& calculator;
		IErrorGenerator<T>& generator;

    public:
		/*
		 * Crée un processeur qui va effectuer des calculs avec des erreurs
		 * et tenter de les corriger.
		 * @param calculator le calculateur qui va être utilisé par le processeur
		 */
		Processor(ICalculator<T>& calculator, IErrorGenerator<T>& generator);

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


