#pragma once
#include <iostream>
#include "../settings.hpp"

template <class T> class IMatrix {
    public:
		/*
		 * Donne le nombre de lignes de la matrice.
		 * @return le nombre de lignes
		 */
        virtual int getM() const = 0;

		/*
		 * Donne le nombre de colonnes de la matrice.
		 * @return le nombre de colonnes
		 */
        virtual int getN() const = 0;

		/*
		 * Donne les données contenues dans la matrice.
		 * @return les données sous la forme d'un tableau, où les données sont rangées lignes par lignes
		 */
        virtual T* getData() const = 0;

		/*
		 * Indique si la mémoire a été allouée pour le contenu de la matrice à sa création.
		 * @return vrai si la mémoire a été allouée, faux sinon
		 */
        virtual bool getDataAllocation() const = 0;

		/*
		 * Donne un élément contenu dans la matrice.
		 * remarque : surcharge de l'opérateur "()"
		 * @param i l'indice de ligne
		 * @param j l'indice de colonne
		 * @return l'élément à l'indice i, j
		 */
        virtual T& operator()(int i, int j) const = 0;

		/*
		 * Affecte le contenu d'une autre matrice au contenu de celle-ci.
		 * remarque : redéfinition de l'opérateur "="
		 * @param M la seconde matrice
		 * @return *this
		 */
        virtual IMatrix<T>& operator=(const IMatrix<T>& M) = 0;

		/*
		 * Indique si cette matrice est égale à une autre.
		 * remarque : redéfinition de l'opérateur "=="
		 * @param M la seconde matrice
		 * @return vrai si les deux matrices sont égales
		 */
        virtual bool operator==(const IMatrix<T>& M) const = 0;

		/*
		 * Donne un représentation textuelle de la matrice.
		 * @return la représentation sous la forme d'une chaine
		 */
        virtual string toString() const = 0;

		/*
		 * Donne un identifiant unique pour un couple d'indices i, j.
		 * @param i l'indice de ligne
		 * @param j l'indice de colonne
		 * @return l'identifiant pour la position à l'indice i, j
		 */
        virtual int locationId(int i, int j) const = 0;

		/*
		 * Donne la distance entre cette matrice et une autre.
		 * La distance entre deux matrices est le nombre d'éléments en lesquels elles diffèrent.
		 * (Huang and Abraham : Algorithm-Based Fault Tolerance for Matrix Operations)
		 * @param M la seconde matrice
		 * @return la distance
		 */
        virtual int distance(const IMatrix<T>& M) const = 0;

		/*
		 * Donne le poids de la matrice.
		 * Le poids d'une matrice est le nombre d'éléments non-nulls de celle-ci.
		 * (Huang and Abraham : Algorithm-Based Fault Tolerance for Matrix Operations)
		 * @return le poids
		 */
        virtual int weight() const = 0;
};
