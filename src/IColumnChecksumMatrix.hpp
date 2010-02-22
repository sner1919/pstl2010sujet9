#pragma once
#include "IMatrix.hpp"

template <class T> class IColumnChecksumMatrix : public virtual IMatrix<T> {
    public:
        virtual T* getColumnSummationVector() = 0;
        virtual int columnErrorDetection(int* corruptedColumns) = 0;
};
