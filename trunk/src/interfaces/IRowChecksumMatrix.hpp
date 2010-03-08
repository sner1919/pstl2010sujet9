#pragma once
#include "IMatrix.hpp"
#include "IVector.hpp"

template <class T> class IRowChecksumMatrix : public virtual IMatrix<T> {
    public:
        virtual IVector<T>& getRowSummationVector() = 0;
        virtual T computeRowSum(int i) = 0;
};
