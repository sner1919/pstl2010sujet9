#include "interfaces/ICalculator.hpp"

template <class T> class Processor : public ICalculator<T> {
		ICalculator<T>& calculator;
    
    public:
		/*
		 * Crée un processeur qui va effectuer des calculs avec des erreurs
		 * et tenter de les corriger.
		 * @param calculator le calculateur qui va être utilisé par le processeur
		 */
		Processor(ICalculator<T>& calculator);

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


