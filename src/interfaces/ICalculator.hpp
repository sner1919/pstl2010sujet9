#pragma once
#include "IMatrix.hpp"

template <class T> class ICalculator {
    public:
		/*
		 * Effectue le produit de deux matrices.
		 * @param Res la matrice qui va contenir le résultat
		 * @param A la première matrice
		 * @param B la seconde matrice
		 */
        virtual void mult(IMatrix<T>& Res, IMatrix<T>& A, IMatrix<T>& B) = 0;

		/*
		 * Effectue le produit d'une matrice et d'un scalaire.
		 * @param Res la matrice qui va contenir le résultat
		 * @param A la matrice
		 * @param x le scalaire
		 */
        virtual void mult(IMatrix<T>& Res, IMatrix<T>& A, T x) = 0;

		/*
		 * Effectue la somme de deux matrices.
		 * @param Res la matrice qui va contenir le résultat
		 * @param A la première matrice
		 * @param B la seconde matrice
		 */
        virtual void add(IMatrix<T>& Res, IMatrix<T>& A, IMatrix<T>& B) = 0;

		/*
		 * Effectue la transposition d'une matrice.
		 * @param Res la matrice qui va contenir le résultat
		 * @param A la matrice
		 */
        virtual void transpose(IMatrix<T>& Res, IMatrix<T>& A) = 0;

		/*
		 * Effectue la décomposition LU d'une matrice (trouve L et U tq A = L * U).
		 * @param L la matrice qui va contenir L
		 * @param U la matrice qui va contenir U
		 * @param A la matrice A
		 */
        virtual void LU(IMatrix<T>& L, IMatrix<T>& U, IMatrix<T>& A) = 0;
};
