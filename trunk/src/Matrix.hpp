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
         * @param data le contenu sous la forme d'un tableau, où les données sont rangées lignes par lignes
         * @param m le nombre de lignes
         * @param n le nombre de colonnes
         */
        Matrix(T* data, int m, int n);
        
        ~Matrix();

        // implémentation de IMatrix<T>
        int getM();

        // implémentation de IMatrix<T>
        int getN();

        // implémentation de IMatrix<T>
        T* getData();

        // implémentation de IMatrix<T>
        T& operator()(int i, int j);

        // implémentation de IMatrix<T>
        bool operator==(IMatrix<T>& M);

        // implémentation de IMatrix<T>
        string toString();
};
