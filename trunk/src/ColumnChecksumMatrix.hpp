#pragma once
#include "settings.hpp"
#include "interfaces/IColumnChecksumMatrix.hpp"
#include "Matrix.hpp"

template <class T> class ColumnChecksumMatrix : public virtual Matrix<T>, public virtual IColumnChecksumMatrix<T> {
		IMatrix<T>& matrix;
		IVector<double>& columnSummationVector;

	public:
        /*
		 * Crée une ColumnChecksumMatrix à partir d'une matrice existante (utilisation de la même zone mémoire).
		 * @param M la matrice
		 */
		ColumnChecksumMatrix(IMatrix<T>& M);

		~ColumnChecksumMatrix();

		// redéfinition de Matrix<T>
		TYPE_UNION operator()(int i, int j) const;

        // implémentation de IColumnChecksumMatrix<T>
        IMatrix<T>& getColumnMatrix() const;

        // implémentation de IColumnChecksumMatrix<T>
        IVector<double>& getColumnSummationVector() const;

        // implémentation de IColumnChecksumMatrix<T>
        double computeColumnSum(int j) const;

        // implémentation de IColumnChecksumMatrix<T>
        bool columnErrorDetection(int j) const;

        // implémentation de IColumnChecksumMatrix<T>
        bool columnErrorDetection() const;
};
