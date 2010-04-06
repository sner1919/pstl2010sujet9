#pragma once
#include "IMatrix.hpp"
#include "IVector.hpp"

template <class T> class IRowChecksumMatrix : public virtual IMatrix<T> {
    public:
		/*
		 * Donne le vecteur de sommation des lignes de la matrice.
		 * return le vecteur de sommation
		 */
        virtual IVector<T>& getRowSummationVector() const = 0;

        /*
		 * Effectue la sommation d'une ligne de la matrice.
		 * @param i l'indice de la ligne
		 * return le résultat de la sommation
		 */
        virtual T computeRowSum(int i) const = 0;
};
