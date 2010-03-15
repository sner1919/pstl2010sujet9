#include "Processor.hpp"
#include "FullChecksumMatrix.hpp"

template <class T>
Processor<T>::Processor(ICalculator<T>& calculator) : calculator(calculator){}

template <class T>
void Processor<T>::mult(IMatrix<T>& Res,IMatrix<T>& A, IMatrix<T>& B){
	FullChecksumMatrix<T> Resf(Res);
	ColumnChecksumMatrix<T> Ac(A);
	RowChecksumMatrix<T> Br(B);
	calculator.mult(Resf, Ac, Br);
	Resf.errorCorrection();
}

template <class T>
void Processor<T>::mult(IMatrix<T>& Res,IMatrix<T>& A, T x){
	calculator.mult(Res, A, x);
}

template <class T>
void Processor<T>::add(IMatrix<T>& Res,IMatrix<T>& A, IMatrix<T>& B){
	calculator.add(Res, A, B);
}

template <class T>
void Processor<T>::transpose(IMatrix<T>& Res, IMatrix<T>& A){
	calculator.transpose(Res, A);
}

template <class T>
void Processor<T>::LU(IMatrix<T>& L, IMatrix<T>& U, IMatrix<T>& A){
	calculator.LU(L, U, A);
}

template class Processor<double>;
