#pragma once
#include "interfaces/IFullChecksumMatrix.hpp"
#include "RowChecksumMatrix.hpp"
#include "ColumnChecksumMatrix.hpp"
#include <stdlib.h>
#include <vector>

template <class T> class FullChecksumMatrix : public virtual Matrix<T>, public IFullChecksumMatrix<T> {
		IRowChecksumMatrix<T>* RCM;
		IColumnChecksumMatrix<T>* CCM;

	public:
        /*
         * Crée une copie d'une FullChecksumMatrix existante.
         * @param M la FullChecksumMatrix existante
         */
		FullChecksumMatrix(const IFullChecksumMatrix<T>& M);

		/*
		 * Crée une FullChecksumMatrix à partir d'une matrice existante (utilisation de la même zone mémoire).
		 * @param M la matrice
		 */
		FullChecksumMatrix(IMatrix<T>& M);

        ~FullChecksumMatrix();

        // redéfinition de Matrix<T>
        T& operator()(int i, int j) const;

        // implémentation de IFullChecksumMatrix<T>
        IVector<T>& getRowSummationVector() const;

        // implémentation de IFullChecksumMatrix<T>
        T computeRowSum(int i) const;

        // implémentation de IFullChecksumMatrix<T>
        IVector<T>& getColumnSummationVector() const;

        // implémentation de IFullChecksumMatrix<T>
        T computeColumnSum(int j) const;

        // implémentation de IFullChecksumMatrix<T>
        bool errorCorrection();
};
