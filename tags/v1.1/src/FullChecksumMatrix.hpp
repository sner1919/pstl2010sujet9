#pragma once
#include "interfaces/IFullChecksumMatrix.hpp"
#include "RowChecksumMatrix.hpp"
#include "ColumnChecksumMatrix.hpp"
#include <stdlib.h>
#include <vector>

template <class T> class FullChecksumMatrix : public ColumnChecksumMatrix<T>, public RowChecksumMatrix<T>, public virtual IFullChecksumMatrix<T> {
	public:
        /*
		 * Crée une FullChecksumMatrix à partir d'une matrice existante (utilisation de la même zone mémoire).
		 * @param M la matrice
		 */
		FullChecksumMatrix(IMatrix<T>& M);

        ~FullChecksumMatrix();

        // redéfinition de Matrix<T>
        T& operator()(int i, int j) const;

        // implémentation de IFullChecksumMatrix<T>
        bool errorCorrection();
};
