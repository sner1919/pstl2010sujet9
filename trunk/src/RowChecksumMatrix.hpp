#pragma once
#include "interfaces/IRowChecksumMatrix.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include <stdlib.h>

template <class T> class RowChecksumMatrix : public virtual Matrix<T>, public virtual IRowChecksumMatrix<T> {
		IMatrix<T>& matrix;
		IVector<T>& rowSummationVector;

	public:
        /*
		 * Crée une RowChecksumMatrix à partir d'une RowChecksumMatrix existante (utilisation de la même zone mémoire).
		 * Permet à FullChecksumMatrix d'hériter d'une RowChecksumMatrix qu'elle a créé
		 * @param RCM la RowChecksumMatrix
		 */
		RowChecksumMatrix(RowChecksumMatrix<T>& RCM);

        /*
		 * Crée une RowChecksumMatrix à partir d'une matrice existante (utilisation de la même zone mémoire).
		 * @param M la matrice
		 */
		RowChecksumMatrix(IMatrix<T>& M);

		~RowChecksumMatrix();

		// redéfinition de Matrix<T>
        T& operator()(int i, int j) const;

        // implémentation de IRowChecksumMatrix<T>
        IMatrix<T>& getRowMatrix() const;

        // implémentation de IRowChecksumMatrix<T>
        IVector<T>& getRowSummationVector() const;

        // implémentation de IRowChecksumMatrix<T>
        T computeRowSum(int i) const;

        // implémentation de IRowChecksumMatrix<T>
        bool rowErrorDetection() const;
};
