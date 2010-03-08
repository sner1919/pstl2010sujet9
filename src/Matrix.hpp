#pragma once
#include "interfaces/IMatrix.hpp"
#include <sstream>
#include <stdexcept>

template <class T>
class Matrix : public virtual IMatrix<T> {
        T* data;
        int m, n;
        bool dataAllocation;
        
    public:
        /*
         * Crée une matrice (en allouant la mémoire pour son contenu).
         * @param m le nombre de lignes
         * @param n le nombre de colonnes
         */
        Matrix(int m, int n);

        /*
         * Crée une matrice à partir d'un contenu existant (utilisation de la même zone mémoire).
         * @param m le nombre de lignes
         * @param n le nombre de colonnes
         */
        Matrix(T* data, int m, int n);
        
        ~Matrix();

        int getM();

        int getN();

        T* getData();

        T& operator()(int i, int j);

        bool operator==(IMatrix<T>& M);

        string toString();
};
