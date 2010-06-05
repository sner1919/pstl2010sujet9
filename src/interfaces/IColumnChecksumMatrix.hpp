#pragma once
#include "../settings.hpp"
#include "IMatrix.hpp"
#include "IVector.hpp"

template <class T> class IColumnChecksumMatrix : public virtual IMatrix<T> {
    public:
		/*
		 * Donne la matrice.
		 * @return la matrice
		 */
		virtual IMatrix<T>& getColumnMatrix() const = 0;

		/*
		 * Donne le vecteur de sommation des colonnes de la matrice.
		 * @return le vecteur de sommation
		 */
        virtual IVector<TYPE_SUM>& getColumnSummationVector() const = 0;

        /*
		 * Effectue la sommation d'une colonne de la matrice.
		 * @param j l'indice de la colonne
		 * @return le résultat de la sommation
		 */
        virtual TYPE_SUM computeColumnSum(int j) const = 0;

        /*
		 * Indique si une erreur a été détectée dans une colonne.
		 * @param j l'indice de la ligne
		 * @return vrai si au moins une erreur a été détectée, faux sinon
		 */
        virtual bool columnErrorDetection(int j) const = 0;

        /*
		 * Indique si une erreur a été détectée dans une colonne.
		 * @return vrai si au moins une erreur a été détectée, faux sinon
		 */
        virtual bool columnErrorDetection() const = 0;
};
