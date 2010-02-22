#pragma once
#include "IMatrix.hpp"

template <class T> class ICalculator {
    public:
        virtual void mult(IMatrix<T>& Res, IMatrix<T>& A, IMatrix<T>& B) = 0;
        virtual void mult(IMatrix<T>& Res, IMatrix<T>& A, T x) = 0;
        virtual void add(IMatrix<T>& Res, IMatrix<T>& A, IMatrix<T>& B) = 0;
        virtual void transpose(IMatrix<T>& Res, IMatrix<T>& A) = 0;
        virtual void LU(IMatrix<T>& L, IMatrix<T>& U, IMatrix<T>& A) = 0;
};
