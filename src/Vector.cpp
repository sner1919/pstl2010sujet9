#include "Vector.hpp"

template <class T>
Vector<T>::Vector(const Vector<T>& V) : Matrix<T>(V) {}

template <class T>
Vector<T>::Vector(int m, bool line) : Matrix<T>(line ? 1 : m, line ? m : 1), line(line) {}

template <class T>
Vector<T>::Vector(T* data, int m, bool line) : Matrix<T>(data, line ? 1 : m, line ? m : 1), line(line) {}

template <class T>
PSTL_TYPE_UNION Vector<T>::operator()(int i) const {
	return Matrix<T>::operator()(1, i);
}

template class Vector<double>;
template class Vector<TYPE_SUM>;
