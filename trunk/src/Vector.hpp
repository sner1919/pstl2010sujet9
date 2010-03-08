#pragma once
#include "interfaces/IVector.hpp"
#include "Matrix.hpp"

template <class T>
class Vector : public Matrix<T>, public IVector<T> {
	public:
		Vector(int m);
		Vector(T* data, int m);
        T& operator()(int i);
};
