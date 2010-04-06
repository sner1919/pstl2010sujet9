#include "Processor.hpp"

template <class T>
Processor<T>::Processor(ICalculator<T>& calculator, IErrorGenerator<T>& generator) : calculator(calculator), generator(generator) {}

template <class T>
void Processor<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	//FullChecksumMatrix<T> Resf(Res);
	//ColumnChecksumMatrix<T> Ac((IMatrix<T>&) A);
	RowChecksumMatrix<T> Br((IMatrix<T>&) B);
	//generator.generateError(Resf, 1, 1, Resf.getM(), 1, Resf.getN());
	calculator.mult(Res, A, B);
	//Resf.errorCorrection();
}

template <class T>
void Processor<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, T x) const {
	calculator.mult(Res, A, x);
}

template <class T>
void Processor<T>::add(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	calculator.add(Res, A, B);
}

template <class T>
void Processor<T>::transpose(IMatrix<T>& Res, const IMatrix<T>& A) const {
	calculator.transpose(Res, A);
}

template <class T>
void Processor<T>::LU(IMatrix<T>& L, IMatrix<T>& U, const IMatrix<T>& A) const {
	calculator.LU(L, U, A);
}

template class Processor<PSTL_TYPE>;
