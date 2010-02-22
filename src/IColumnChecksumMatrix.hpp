#pragma once
#include "IMatrix.hpp"
#include "IVector.hpp"

template <class T> class IColumnChecksumMatrix : public virtual IMatrix<T> {
    public:
        virtual IVector<T>& getColumnSummationVector() = 0;
        virtual int columnErrorDetection(int* corruptedColumns) = 0;
};
