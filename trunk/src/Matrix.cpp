#pragma once
#include "IMatrix.hpp"
#include <sstream>
#include <stdexcept>

template <class T> class Matrix : public virtual IMatrix<T> {
        T* data;
        int m, n;
        bool dataAllocation;
        
    public:
        /*
         * Crée une matrice (en allouant la mémoire pour son contenu).
         * @param m le nombre de lignes
         * @param n le nombre de colonnes
         */
        Matrix(int m, int n) {
            this->data = new T[m * n];
            this->m = m;
            this->n = n;
            dataAllocation = true;
        }

        /*
         * Crée une matrice à partir d'un contenu existant (utilisation de la même zone mémoire).
         * @param m le nombre de lignes
         * @param n le nombre de colonnes
         */
        Matrix(T* data, int m, int n) {
            this->data = data;
            this->m = m;
            this->n = n;
            dataAllocation = false;
        }
        
        ~Matrix() {
        	if(dataAllocation) delete [] data;
        }
        
        int getM() {
            return m;
        }
        
        int getN() {
            return n;
        }
        
        T* getData() {
            return data;
        }

        T& operator()(int i, int j) {
            return data[(i - 1) * n + (j - 1)];
        }
        
        bool operator==(IMatrix<T>& M) {
        	for(int i = 1; i <= getM(); i++){
				for(int j = 1; j <= getN(); j++){
					if((*this)(i, j) != M(i, j)) return false;
				}
			}
        	return true;
        }

        string toString() {
            ostringstream oss;
            
            oss << "[" << endl;
            for(int i = 1; i <= getM(); i++){
                for(int j = 1; j <= getN(); j++){
                    oss << (*this)(i, j) << " ";
                }
                oss << endl;
            }
            oss << "]" << endl;
            
            return oss.str();
        }
};
