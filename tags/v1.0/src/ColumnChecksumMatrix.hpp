#pragma once
#include "interfaces/IColumnChecksumMatrix.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include <stdlib.h>

template <class T> class ColumnChecksumMatrix : public virtual Matrix<T>, public virtual IColumnChecksumMatrix<T> {
		IMatrix<T>& matrix;
		IVector<T>& columnSummationVector;

	public:
        /*
		 * Crée une ColumnChecksumMatrix à partir d'une matrice existante (utilisation de la même zone mémoire).
		 * @param M la matrice
		 */
		ColumnChecksumMatrix(IMatrix<T>& M);

		~ColumnChecksumMatrix();

		// redéfinition de Matrix<T>
		T& operator()(int i, int j) const;

        // implémentation de IColumnChecksumMatrix<T>
        IMatrix<T>& getColumnMatrix() const;

        // implémentation de IColumnChecksumMatrix<T>
        IVector<T>& getColumnSummationVector() const;

        // implémentation de IColumnChecksumMatrix<T>
        T computeColumnSum(int j) const;

        // implémentation de IColumnChecksumMatrix<T>
        bool columnErrorDetection() const;
};