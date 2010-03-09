#pragma once
#include "interfaces/IVector.hpp"
#include "Matrix.hpp"

template <class T>
class Vector : public Matrix<T>, public IVector<T> {
	public:
		/*
		 * Crée un vecteur (en allouant la mémoire pour son contenu).
		 * @param m le nombre d'éléments
		 */
		Vector(int m);

		/*
		 * Crée un vecteur à partir d'un contenu existant (utilisation de la même zone mémoire).
         * @param data le contenu sous la forme d'un tableau
		 * @param m le nombre d'éléments
		 */
		Vector(T* data, int m);

        // implémentation de IVector<T>
        T& operator()(int i);
};
