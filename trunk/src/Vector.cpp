#include "Vector.hpp"

template <class T>
Vector<T>::Vector(int m) : Matrix<T>(m, 1) {
}

template <class T>
Vector<T>::Vector(T* data, int m) : Matrix<T>(data, m, 1) {
}

template <class T>
T& Vector<T>::operator()(int i){
	return Matrix<T>::operator()(i, 1);
}

template class Vector<double>;
