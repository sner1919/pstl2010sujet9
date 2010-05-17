#pragma once
#include "settings.hpp"
#include "interfaces/IVector.hpp"
#include "Matrix.hpp"

template <class T>
class Vector : public Matrix<T>, public virtual IVector<T> {
		bool line;

	public:
		/*
		 * Crée une copie d'un vecteur existant.
		 * @param V le vecteur existant
		 */
		Vector(const Vector<T>& V);

		/*
		 * Crée un vecteur (en allouant la mémoire pour son contenu).
		 * @param m le nombre d'éléments
		 * @param line indique s'il s'agit d'un vecteur colonne
		 */
		Vector(int m, bool line);

		/*
		 * Crée un vecteur à partir d'un contenu existant (utilisation de la même zone mémoire).
         * @param data le contenu sous la forme d'un tableau
		 * @param m le nombre d'éléments
		 * @param line indique s'il s'agit d'un vecteur colonne
		 */
		Vector(T* data, int m, bool line);

        // implémentation de IVector<T>
		PSTL_TYPE_UNION operator()(int i) const;
};
