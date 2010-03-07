#pragma once
#include <iostream>
using namespace std;

template <class T> class IMatrix {
    public:
		/*
		 * Donne le nombre de lignes de la matrice.
		 * @return le nombre de lignes
		 */
        virtual int getM() = 0;

		/*
		 * Donne le nombre de colonnes de la matrice.
		 * @return le nombre de colonnes
		 */
        virtual int getN() = 0;

		/*
		 * Donne les données contenues dans la matrice.
		 * @return les données sous la forme d'un tableau, où les données sont rangées lignes par lignes
		 */
        virtual T* getData() = 0;

		/*
		 * Donne un élément contenu dans la matrice.
		 * remarque : redéfinition de l'opérateur "()"
		 * @param i l'indice de ligne
		 * @param j l'indice de colonne
		 * @return l'élément à l'indice i, j
		 */
        virtual T& operator()(int i, int j) = 0;

		/*
		 * Indique si cette matrice est égale à une autre.
		 * remarque : redéfinition de l'opérateur "=="
		 * @param M la seconde matrice
		 * @return vrai si les deux matrices sont égales
		 */
        virtual bool operator==(IMatrix<T>& M) = 0;

		/*
		 * Donne un représentation textuelle de la matrice.
		 * @return la représentation sous la forme d'une chaine
		 */
        virtual string toString() = 0;
};
