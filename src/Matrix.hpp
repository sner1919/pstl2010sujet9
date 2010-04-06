#pragma once
#include "interfaces/IMatrix.hpp"
#include <gmpxx.h>
#include <sstream>
#include <stdexcept>
#include "math.h"
#include "stdio.h"

template <class T>
class Matrix : public virtual IMatrix<T> {
        union {T* data; IMatrix<T>* M;};
        int m, n;
        bool dataAllocation;
        
	protected:
        /*
         * Crée une matrice à partir d'une matrice existante (utilisation de la même zone mémoire).
         * @param M la matrice existante
         * @param m le nombre de lignes
         * @param n le nombre de colonnes
         */
        Matrix(IMatrix<T>& M, int m, int n);

    public:
        /*
         * Crée une copie d'une matrice existante.
         * @param M la matrice existante
         */
        Matrix(const IMatrix<T>& M);

        /*
         * Crée une matrice (en allouant la mémoire pour son contenu).
         * @param m le nombre de lignes
         * @param n le nombre de colonnes
         */
        Matrix(int m, int n);

        /*
         * Crée une matrice à partir d'un contenu existant (utilisation de la même zone mémoire).
         * @param data le contenu sous la forme d'un tableau, où les données sont rangées lignes par lignes
         * @param m le nombre de lignes
         * @param n le nombre de colonnes
         */
        Matrix(T* data, int m, int n);

        ~Matrix();

        // implémentation de IMatrix<T>
        int getM() const;

        // implémentation de IMatrix<T>
        int getN() const;

        // implémentation de IMatrix<T>
        T* getData() const;

        // implémentation de IMatrix<T>
        T& operator()(int i, int j) const;

        // implémentation de IMatrix<T>
        IMatrix<T>& operator=(const IMatrix<T>& M);

        // implémentation de IMatrix<T>
        bool operator==(const IMatrix<T>& M) const;

        // implémentation de IMatrix<T>
        int distance(const IMatrix<T>& M) const;

        // implémentation de IMatrix<T>
        int weight() const;

        // implémentation de IMatrix<T>
        string toString() const;

        // implémentation de IMatrix<T>
        int locationId(int i, int j) const;
};
