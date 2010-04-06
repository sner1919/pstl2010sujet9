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
void CalculatorAtlas<T>::LU(IMatrix<T>& L, IMatrix<T>& U, const IMatrix<T>& A) const {
	// Vérifications
	if(!(A.getM() == A.getN()
		 && A.getM() == L.getM() && A.getM() == L.getN()
		 && A.getM() == U.getM() && A.getM() == U.getN())) throw domain_error("décomposition LU impossible");
}

template class CalculatorAtlas<PSTL_TYPE>;
