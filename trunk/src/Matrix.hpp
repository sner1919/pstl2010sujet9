#pragma once
#include "interfaces/IMatrix.hpp"
#include <gmpxx.h>
#include <sstream>
#include <stdexcept>
#include "math.h"
#include "stdio.h"

template <class T>
class Matrix : public virtual IMatrix<T> {
        int m, n;
        T* data;
        bool dataAllocation;

    public:
        /*
         * Crée une copie d'une matrice existante.
         * @param M la matrice existante
         */
        Matrix(const Matrix<T>& M);

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
        bool getDataAllocation() const;

        // implémentation de IMatrix<T>
        T& operator()(int i, int j) const;

        // implémentation de IMatrix<T>
        IMatrix<T>& operator=(const IMatrix<T>& M);

        // implémentation de IMatrix<T>
        bool operator==(const IMatrix<T>& M) const;

        // implémentation de IMatrix<T>
        string toString() const;

        // implémentation de IMatrix<T>
        void fromDouble(double* t, bool rowMajor);

        // implémentation de IMatrix<T>
        void toDouble(double* t, bool rowMajor) const;

        // implémentation de IMatrix<T>
        int locationId(int i, int j) const;

        // implémentation de IMatrix<T>
        int distance(const IMatrix<T>& M) const;

        // implémentation de IMatrix<T>
        int weight() const;
};
