#pragma once
#include "interfaces/IRowChecksumMatrix.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include <stdlib.h>

template <class T> class RowChecksumMatrix : public virtual Matrix<T>, public IRowChecksumMatrix<T> {
		IVector<T>* rowSummationVector;

	public:
        /*
         * Crée une copie d'une RowChecksumMatrix existante.
         * @param M la RowChecksumMatrix existante
         */
		RowChecksumMatrix(const IRowChecksumMatrix<T>& M);

		 /*
		 * Crée une RowChecksumMatrix à partir d'une matrice existante (utilisation de la même zone mémoire).
		 * @param M la matrice
		 */
		RowChecksumMatrix(IMatrix<T>& M);

		~RowChecksumMatrix();

		// redéfinition de Matrix<T>
        T& operator()(int i, int j) const;

        // implémentation de IRowChecksumMatrix<T>
        IVector<T>& getRowSummationVector() const;

        // implémentation de IRowChecksumMatrix<T>
        T computeRowSum(int i) const;
};
