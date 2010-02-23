#pragma once
#include "IRowChecksumMatrix.hpp"
#include "IColumnChecksumMatrix.hpp"

template <class T> class IFullChecksumMatrix : public virtual IRowChecksumMatrix<T>, public virtual IColumnChecksumMatrix<T> {
    public:
//        virtual int getSummationsVectorIntersection() = 0;
//        virtual int* errorDetection() = 0;
//        virtual int*[2] errorLocation() = 0;
//        virtual bool errorCorrection() = 0;
//        virtual bool process() = 0;
};
