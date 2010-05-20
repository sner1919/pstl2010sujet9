#include "CalculatorNaive.hpp"

template <class T>
void CalculatorNaive<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	CalculatorNaiveMult<T, T, T>(Res, A, B);
}

template <class T>
void CalculatorNaive<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, T x) const {
	// Vérifications
	if(!(Res.getM() == A.getM() && Res.getN() == A.getN())) throw domain_error("produit impossible");

	for(int i = 1; i <= Res.getM(); i++){
		for(int j = 1; j<= Res.getN(); j++) {
			Res(i, j) = A(i, j).toTypeSum() * x;
		}
	}
}

template <class T>
void CalculatorNaive<T>::add(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	// Vérifications
	if(!(A.getM() == B.getM() && A.getM() == Res.getM()
		 && A.getN() == B.getN() && A.getN() == Res.getN())) throw domain_error("addition impossible");

	for(int i = 1; i <= Res.getM(); i++){
		for(int j = 1; j <= Res.getN(); j++) {
			Res(i, j) = A(i, j).toTypeSum() + B(i, j).toTypeSum();
		}
	}
}

template <class T>
void CalculatorNaive<T>::transpose(IMatrix<T>& Res, const IMatrix<T>& A) const {
	// Vérifications
	if(!(A.getM() == Res.getN() && A.getN() == Res.getM())) throw domain_error("transposition impossible");

	for(int i = 1; i <= Res.getM(); i++){
		for(int j = 1; j <= Res.getN(); j++) Res(j, i) = A(i, j);
	}
}

// Algorithme d'après "Huang and Abraham : Algorithm-Based Fault Tolerance for Matrix Operations"
// Hypothèse : la matrice A est LU décomposable (sans pivotements).
template <class T>
void CalculatorNaive<T>::LU(IMatrix<T>& P, IMatrix<T>& L, IMatrix<T>& U, const IMatrix<T>& A) const {
	// Vérifications
	if(!(A.getM() == L.getM() && A.getN() == U.getN()
		 && A.getM() == A.getN())) throw domain_error("décomposition LU impossible");

	PSTL_TYPE_SUM** c = new PSTL_TYPE_SUM*[A.getM()];
	for(int i = 1; i <= A.getM(); i++) {
		c[i-1] = new PSTL_TYPE_SUM[A.getM()];
		for(int j = 1; j <= A.getM(); j++) {
			c[i-1][j-1] = A(i, j).toTypeSum();

			// matrice de permutation
			P(i, j) = i == j ? 1 : 0;
		}
	}

	for(int k = 1; k <= L.getN(); k++) {
		for(int i = 1; i <= A.getM(); i++) {
			if(k > i) U(k, i) = 0;
			else U(k, i) = c[k-1][i-1];

			if(i < k) L(i, k) = 0;
			else if(i == k) L(i, k) = 1;
			else L(i, k) = c[i-1][k-1] / U(k, k).toTypeSum();
		}

		for(int i = 1; i <= A.getM(); i++) {
			for(int j = 1; j <= A.getM(); j++){
				c[i-1][j-1] += L(i, k).toTypeSum() * -U(k, j).toTypeSum();
			}
		}
	}

	// liberation de la mémoire
	for(int i = 0; i < A.getM(); i++) delete [] c[i];
	delete [] c;
}

template class CalculatorNaive<double>;

template <class T1, class T2, class T3> void CalculatorNaiveMult(IMatrix<T1>& Res, const IMatrix<T2>& A, const IMatrix<T3>& B) {
	// Vérifications
	if(!(A.getN() == B.getM()
		 && Res.getM() == A.getM() && Res.getN() == B.getN())) throw domain_error("produit impossible");

    mpf_set_default_prec(512);
	PSTL_TYPE_SUM s;

	for(int i = 1; i <= Res.getM(); i++) {
		for(int j = 1; j <= Res.getN(); j++) {
			s = 0;
			for(int k = 1; k <= A.getN(); k++) {
				s += A(i, k).toTypeSum() * B(k, j).toTypeSum();
			}
			Res(i, j) = s;
		}
	}
}

template <class T1, class T2, class T3> void CalculatorNaiveMult(IMatrix<T1>& Res, const IMatrix<T2>& A, T3 x) {

}

template <class T1, class T2, class T3> void CalculatorNaiveAdd(IMatrix<T1>& Res, const IMatrix<T2>& A, const IMatrix<T3>& B) {

}

template <class T1, class T2, class T3> void CalculatorNaiveTranspose(IMatrix<T1>& Res, const IMatrix<T2>& A) {

}

template <class T1, class T2, class T3, class T4> void CalculatorNaiveLU(IMatrix<T1>& P, IMatrix<T2>& L, IMatrix<T3>& U, const IMatrix<T4>& A) {

}

template void CalculatorNaiveMult(IMatrix<PSTL_TYPE_SUM>&, const IMatrix<PSTL_TYPE_SUM>&, const IMatrix<double>&);
template void CalculatorNaiveMult(IMatrix<PSTL_TYPE_SUM>&, const IMatrix<double>&, const IMatrix<PSTL_TYPE_SUM>&);
