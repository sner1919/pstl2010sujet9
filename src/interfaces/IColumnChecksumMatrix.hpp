#pragma once
#include "IMatrix.hpp"
#include "IVector.hpp"

template <class T> class IColumnChecksumMatrix : public virtual IMatrix<T> {
    public:
		/*
		 * Donne le vecteur de sommation des colonnes de la matrice.
		 * return le vecteur de sommation
		 */
        virtual IVector<T>& getColumnSummationVector() const = 0;

        /*
		 * Effectue la sommation d'une colonne de la matrice.
		 * @param j l'indice de la colonne
		 * return le résultat de la sommation
		 */
        virtual T computeColumnSum(int j) const = 0;
};
