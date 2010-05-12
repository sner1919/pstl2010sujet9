#include "Processor.hpp"
#include <pthread.h>

template <class T>
Processor<T>::Processor(ICalculator<T>& calculator, IErrorGenerator<T>& generator) : calculator(calculator), generator(generator) {}

template <class T>
void Processor<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	FullChecksumMatrix<T> Resf(Res);
	ColumnChecksumMatrix<T> Ac((IMatrix<T>&) A);
	RowChecksumMatrix<T> Br((IMatrix<T>&) B);

	pthread_t th = generator.generateError(Resf, 1, 1, Resf.getM(), 1, Resf.getN());
	calculator.mult(Resf, Ac, Br);
	pthread_join(th, NULL);
	Resf.errorCorrection();
}

template <class T>
void Processor<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, T x) const {
	FullChecksumMatrix<T> Resf(Res);
	FullChecksumMatrix<T> Af((IMatrix<T>&) A);

	pthread_t th = generator.generateError(Resf, 1, 1, Resf.getM(), 1, Resf.getN());
	calculator.mult(Resf, Af, x);
	pthread_join(th, NULL);
	Resf.errorCorrection();
}

template <class T>
void Processor<T>::add(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	FullChecksumMatrix<T> Resf(Res);
	FullChecksumMatrix<T> Af((IMatrix<T>&) A);
	FullChecksumMatrix<T> Bf((IMatrix<T>&) B);

	pthread_t th = generator.generateError(Resf, 1, 1, Resf.getM(), 1, Resf.getN());
	calculator.add(Resf, Af, Bf);
	pthread_join(th, NULL);
	Resf.errorCorrection();
}

template <class T>
void Processor<T>::transpose(IMatrix<T>& Res, const IMatrix<T>& A) const {
	FullChecksumMatrix<T> Resf(Res);
	FullChecksumMatrix<T> Af((IMatrix<T>&) A);

	pthread_t th = generator.generateError(Resf, 1, 1, Resf.getM(), 1, Resf.getN());
	calculator.transpose(Resf, Af);
	pthread_join(th, NULL);
	Resf.errorCorrection();
}

template <class T>
void Processor<T>::LU(IMatrix<T>& P, IMatrix<T>& L, IMatrix<T>& U, const IMatrix<T>& A) const {
	FullChecksumMatrix<T> Pf(P);
	ColumnChecksumMatrix<T> Lc(L);
	RowChecksumMatrix<T> Ur(U);
	FullChecksumMatrix<T> Af((IMatrix<T>&) A);

	pthread_t th1 = generator.generateError(Pf, 1, 1, Pf.getM(), 1, Pf.getN());
	pthread_t th2 = generator.generateError(Lc, 1, 1, Lc.getM(), 1, Lc.getN());
	pthread_t th3 = generator.generateError(Ur, 1, 1, Ur.getM(), 1, Ur.getN());
	calculator.LU(Pf, Lc, Ur, Af);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th3, NULL);
	while(Lc.columnErrorDetection() || Ur.rowErrorDetection()) calculator.LU(Pf, Lc, Ur, Af);
}

template class Processor<PSTL_TYPE>;
