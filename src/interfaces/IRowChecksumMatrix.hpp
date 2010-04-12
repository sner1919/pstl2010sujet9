#pragma once
#include "IMatrix.hpp"
#include "IVector.hpp"

template <class T> class IRowChecksumMatrix : public virtual IMatrix<T> {
    public:
		/*
		 * Donne la matrice.
		 * @return la matrice
		 */
		virtual IMatrix<T>& getRowMatrix() const = 0;

		/*
		 * Donne le vecteur de sommation des lignes de la matrice.
		 * @return le vecteur de sommation
		 */
        virtual IVector<T>& getRowSummationVector() const = 0;

        /*
		 * Effectue la sommation d'une ligne de la matrice.
		 * @param i l'indice de la ligne
		 * @return le résultat de la sommation
		 */
        virtual T computeRowSum(int i) const = 0;

        /*
		 * Indique si une erreur a été détectée dans une ligne.
		 * @return vrai si au moins une erreur a été détectée, faux sinon
		 */
        virtual bool rowErrorDetection() const = 0;
};
