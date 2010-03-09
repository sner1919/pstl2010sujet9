#pragma once
#include "interfaces/IRowChecksumMatrix.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include <stdlib.h>

template <class T> class RowChecksumMatrix : public virtual Matrix<T>, public virtual IRowChecksumMatrix<T> {
		IMatrix<T>& M;
		IVector<T>* rowSummationVector;

	public:
		 /*
		 * Crée une RowChecksumMatrix à partir d'une matrice existante (utilisation de la même zone mémoire).
		 * @param M la matrice
		 */
		RowChecksumMatrix(IMatrix<T>& M);

		~RowChecksumMatrix();

		// redéfinition de Matrix<T>
        T& operator()(int i, int j);

        // implémentation de IRowChecksumMatrix<T>
        IVector<T>& getRowSummationVector();

        // implémentation de IRowChecksumMatrix<T>
        T computeRowSum(int i);
};
