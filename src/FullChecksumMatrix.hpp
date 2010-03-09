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
		 * Crée une FullChecksumMatrix à partir d'une matrice existante (utilisation de la même zone mémoire).
		 * @param M la matrice
		 */
		FullChecksumMatrix(IMatrix<T>& M);

        ~FullChecksumMatrix();

        // redéfinition de Matrix<T>
        T& operator()(int i, int j);

        // implémentation de IFullChecksumMatrix<T>
        IVector<T>& getRowSummationVector();

        // implémentation de IFullChecksumMatrix<T>
        T computeRowSum(int i);

        // implémentation de IFullChecksumMatrix<T>
        IVector<T>& getColumnSummationVector();

        // implémentation de IFullChecksumMatrix<T>
        T computeColumnSum(int j);

        // implémentation de IFullChecksumMatrix<T>
        void errorCorrection();
};
