#include "CalculatorAtlas.hpp"

template <class T>
void CalculatorAtlas<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	// Vérifications
	if(!(A.getN() == B.getM()
		 && Res.getM() == A.getM() && Res.getN() == B.getN())) throw domain_error("produit impossible");

	cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
		A.getM(), B.getN(), A.getN(),
		1.0, (const double *) A.getData(), A.getM(),
		(const double *) B.getData(), B.getM(),
		0.0, (double *) Res.getData(), Res.getM());
}

template <class T>
void CalculatorAtlas<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, T x) const {
	// Vérifications
	if(!(Res.getM() == A.getM() && Res.getN() == A.getN())) throw domain_error("produit impossible");
}

template <class T>
void CalculatorAtlas<T>::add(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	// Vérifications
	if(!(A.getM() == B.getM() && A.getM() == Res.getM()
		 && A.getN() == B.getN() && A.getN() == Res.getN())) throw domain_error("addition impossible");
}

template <class T>
void CalculatorAtlas<T>::transpose(IMatrix<T>& Res, const IMatrix<T>& A) const {
	// Vérifications
	if(!(A.getM() == Res.getN() && A.getN() == Res.getM())) throw domain_error("transposition impossible");
}

template <class T>
void CalculatorAtlas<T>::LU(IMatrix<T>& L, IMatrix<T>& U, const IMatrix<T>& A) const {
	// Vérifications
	if(!(A.getM() == L.getM() && A.getN() == U.getN()
		 && A.getM() == A.getN())) throw domain_error("décomposition LU impossible");
}

template class CalculatorAtlas<PSTL_TYPE>;
