#pragma once
#include "IMatrix.hpp"

template <class T> class IVector : public virtual IMatrix<T> {
    public:
		virtual T& operator()(int i) = 0;
};
