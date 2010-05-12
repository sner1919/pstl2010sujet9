#include "CalculatorBlasLapack.hpp"

template <class T>
CalculatorBlasLapack<T>::CalculatorBlasLapack(IBlasLapackAdapter& blasLapackAdapter) : blasLapackAdapter(blasLapackAdapter) {}

template <class T>
void CalculatorBlasLapack<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	// Vérifications
	if(!(A.getN() == B.getM()
		 && Res.getM() == A.getM() && Res.getN() == B.getN())) throw domain_error("produit impossible");

	double *res = new double[Res.getM() * Res.getN()], *a = new double[A.getM() * A.getN()], *b = new double[B.getM() * B.getN()];

	A.toDouble(a, true);
	B.toDouble(b, true);

	blasLapackAdapter.dgemm(CblasRowMajor_, CblasNoTrans_, CblasNoTrans_,
		A.getM(), B.getN(), A.getN(),
		1., (const double *) a, A.getN(),
		(const double *) b, B.getN(),
		0., res, Res.getN());

	Res.fromDouble(res, true);

	delete res; delete a; delete b;
}

template <class T>
void CalculatorBlasLapack<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, T x) const {
	// Vérifications
	if(!(Res.getM() == A.getM() && Res.getN() == A.getN())) throw domain_error("produit impossible");

	double *a = new double[A.getM() * A.getN()];

	A.toDouble(a, true);

	blasLapackAdapter.dscal(Res.getM() * Res.getN(), PSTL_TYPE_TO_DOUBLE(x), a, 1);

	Res.fromDouble(a, true);

	delete a;
}

template <class T>
void CalculatorBlasLapack<T>::add(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	// Vérifications
	if(!(A.getM() == B.getM() && A.getM() == Res.getM()
		 && A.getN() == B.getN() && A.getN() == Res.getN())) throw domain_error("addition impossible");

	double *a = new double[A.getM() * A.getN()], *b = new double[B.getM() * B.getN()];

	A.toDouble(a, true);
	B.toDouble(b, true);

	blasLapackAdapter.daxpy(Res.getM() * Res.getN(), 1, a, 1, b, 1);

	Res.fromDouble(b, true);

	delete a; delete b;
}

template <class T>
void CalculatorBlasLapack<T>::transpose(IMatrix<T>& Res, const IMatrix<T>& A) const {
	// Vérifications
	if(!(A.getM() == Res.getN() && A.getN() == Res.getM())) throw domain_error("transposition impossible");

	for(int i = 1; i <= Res.getM(); i++){
		for(int j = 1; j <= Res.getN(); j++) Res(j, i) = A(i, j);
	}
}

template <class T>
void CalculatorBlasLapack<T>::LU(IMatrix<T>& P, IMatrix<T>& L, IMatrix<T>& U, const IMatrix<T>& A) const {
	// Vérifications
	if(!(A.getM() == L.getM() && A.getN() == U.getN()
		 && A.getM() == A.getN())) throw domain_error("décomposition LU impossible");

	double a[A.getM() * A.getN()];
	int ipiv[A.getM()], piv[A.getM()], aux, m = A.getM(), info = 0;

	A.toDouble(a, false);

	if(blasLapackAdapter.dgetrf(&m, &m, a, &m, ipiv, &info)) throw domain_error("décomposition LU impossible");

	P.fromDouble(a, false);

	// construction de P à partir de ipiv
	for(int i = 1; i <= A.getM(); i++) {
		for(int j = 1; j <= A.getM(); j++) P(i, j) = 0;
		piv[i-1] = i;
	}
	for(int i = A.getM() - 1; i >= 0; i--) {
		aux = piv[ipiv[i] - 1];
		piv[ipiv[i] - 1] = piv[i];
		piv[i] = aux;
	}

	for(int i = 1; i <= A.getM(); i++) {
		P(i, piv[i-1]) = 1;

		for(int j = 1; j <= L.getN(); j++) {
			// L et U
			if(i > j) {
				L(i, j) = a[(j - 1) * A.getN() + (i - 1)];
				U(j, i) = a[(i - 1) * A.getN() + (j - 1)];
			} else if(i == j) {
				L(i, j) = 1;
				U(j, i) = a[(i - 1) * A.getN() + (j - 1)];
			} else {
				L(i, j) = 0;
				U(j, i) = 0;
			}
		}
	}
}

template class CalculatorBlasLapack<PSTL_TYPE>;
