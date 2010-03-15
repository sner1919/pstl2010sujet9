#pragma once
#include "IMatrix.hpp"

template <class T> class IErrorGenerator {
	public:
		/**
		 * injecte une à plusieurs erreurs dans une matrice donnée
		 * pre : iMin > 0, iMax <= M.getM(), jMin > 0, jMax < M.getN()
		 * post : l'indice de ligne de l'erreur injectée sera entre les lignes iMin et iMax
		 * l'indice de colonne de l'erreur injectée sera entre les les colonnes jMin et jMax
		 * @param M la matrice dans laquelle la methode injecte l'erreur
		 * @param nb le nombre d'erreurs à générer
		 * @param iMin l'indice de ligne minimal
		 * @param iMax l'indice de ligne maximal
		 * @param jMin l'indice de colonne minimal
		 * @param jMax l'indice de colonne maximal
		 */
		virtual void generateError(IMatrix<T>& M, int nb, int iMin, int iMax, int jMin, int jMax) = 0;
};
