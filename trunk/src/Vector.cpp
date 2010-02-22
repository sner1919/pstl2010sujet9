#include "IVector.hpp"
#include "Matrix.cpp"

template <class T> class Vector : public Matrix<T>, public IVector<T> {
	public:
		Vector(int m) : Matrix<T>(m, 1) {
		}

		Vector(T* data, int m) : Matrix<T>(data, m, 1) {
		}

        T& operator()(int i){
            return Matrix<T>::operator()(i, 0);
        }
};

