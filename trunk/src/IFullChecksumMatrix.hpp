#pragma once
#include "IRowChecksumMatrix.hpp"
#include "IColumnChecksumMatrix.hpp"

template <class T> class IFullChecksumMatrix : public IRowChecksumMatrix<T>, IColumnChecksumMatrix<T> {
    public:
        virtual int getSummationsVectorIntersection() = 0;
        virtual int* errorDetection() = 0;
        virtual int*[2] errorLocation() = 0;
        virtual bool errorCorrection() = 0;
        virtual bool process() = 0;
};
