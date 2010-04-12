#include "CalculatorNaive.hpp"

template <class T>
void CalculatorNaive<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	// Vérifications
	if(!(A.getN() == B.getM()
		 && Res.getM() == A.getM() && Res.getN() == B.getN())) throw domain_error("produit impossible");

	for(int i = 1; i <= Res.getM(); i++){
		for(int j = 1; j <= Res.getN(); j++){
			Res(i, j) = 0;
			for(int k = 1; k <= A.getN(); k++) Res(i, j) += A(i, k) * B(k, j);
		}
	}
}

template <class T>
void CalculatorNaive<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, T x) const {
	// Vérifications
	if(!(Res.getM() == A.getM() && Res.getN() == A.getN())) throw domain_error("produit impossible");

	for(int i = 1; i <= Res.getM(); i++){
		for(int j = 1; j<= Res.getN(); j++) Res(i, j) = A(i, j) * x;
	}
}

template <class T>
void CalculatorNaive<T>::add(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	// Vérifications
	if(!(A.getM() == B.getM() && A.getM() == Res.getM()
		 && A.getN() == B.getN() && A.getN() == Res.getN())) throw domain_error("addition impossible");

	for(int i = 1; i <= Res.getM(); i++){
		for(int j = 1; j <= Res.getN(); j++) Res(i, j) = A(i, j) + B(i, j);
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
template <class T>
void CalculatorNaive<T>::LU(IMatrix<T>& L, IMatrix<T>& U, const IMatrix<T>& A) const {
	// Vérifications
	if(!(A.getM() == L.getM() && A.getN() == U.getN()
		 && A.getM() == A.getN())) throw domain_error("décomposition LU impossible");

	T** c = new T*[A.getM()];
	for(int i = 1; i <= A.getM(); i++) {
		c[i-1] = new T[A.getM()];
		for(int j = 1; j <= A.getM(); j++) c[i-1][j-1] = A(i, j);
	}

	for(int k = 1; k <= L.getN(); k++) {
		for(int i = 1; i <= A.getM(); i++) {
			if(k > i) U(k, i) = 0;
			else U(k, i) = c[k-1][i-1];

			if(i < k) L(i, k) = 0;
			else if(i == k) L(i, k) = 1;
			else L(i, k) = c[i-1][k-1] / U(k, k);
		}

		for(int i = 1; i <= A.getM(); i++) {
			for(int j = 1; j <= A.getM(); j++) c[i-1][j-1] += L(i, k) * -U(k, j);
		}
	}

	// liberation de la mémoire
	for(int i = 0; i < A.getM(); i++) delete [] c[i];
	delete [] c;
}

template class CalculatorNaive<PSTL_TYPE>;
