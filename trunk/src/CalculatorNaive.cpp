#include "CalculatorNaive.hpp"
#include "Matrix.hpp"

template <class T>
void CalculatorNaive<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	CalculatorNaiveMult<T, T, T>(Res, A, B);
}

template <class T>
void CalculatorNaive<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, T x) const {
	CalculatorNaiveMult<T, T, T>(Res, A, x);
}

template <class T>
void CalculatorNaive<T>::add(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	CalculatorNaiveAdd<T, T, T>(Res, A, B);
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

	TYPE_SUM** c = new TYPE_SUM*[A.getM()];
	for(int i = 1; i <= A.getM(); i++) {
		c[i-1] = new TYPE_SUM[A.getM()];
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

/* +++++++++++++++++++++++ fonctions template  +++++++++++++++++++++++++++ */
template <class T1, class T2, class T3> void CalculatorNaiveMult(IMatrix<T1>& Res, const IMatrix<T2>& A, const IMatrix<T3>& B) {
	// Vérifications
	if(!(A.getN() == B.getM()
		 && Res.getM() == A.getM() && Res.getN() == B.getN())) throw domain_error("produit impossible");
	//Strassen(Res, A, B, pow(ceil(sqrt (max(A.getN(),A.getM()))),2));

    TYPE_SUM s;

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

/*
template <class T1, class T2> void CalculatorNaiveAddBlock(IMatrix<T1>& Res, const IMatrix<T2>& A, int x, int y, int i, int j, int N) {
	for(int k = 1; k <= N; k++){
		for(int l = 1; l <= N; l++){
			TYPE_SUM a = 0;	TYPE_SUM b = 0;
			if(x+k <= A.getN() && y+l <= A.getM()) a = A(x+k,y+l).toTypeSum();
			if(y+l <= A.getN() && j+k <= A.getM()) b = A(i+k,j+k).toTypeSum();
			Res(k,l) = a + b;
		}
	}
}

template <class T1, class T2> void CalculatorNaiveSubBlock(IMatrix<T1>& Res, const IMatrix<T2>& A, int x, int y, int i, int j, int N) {
	for(int k = 1; k <= N; k++){
		for(int l = 1; l <= N; l++){
			TYPE_SUM a = 0;	TYPE_SUM b = 0;
			if(x+k <= A.getN() && y+l <= A.getM()) a = A(x+k,y+l).toTypeSum();
			if(y+l <= A.getN() && j+k <= A.getM()) b = A(i+k,j+k).toTypeSum();
			Res(k,l) = a - b;
		}
	}
}

template <class T1, class T2> void CalculatorNaiveCopyBlock(IMatrix<T1>& Res, const IMatrix<T2>& A, int x, int y, int N) {
	for(int k = 1; k <= N; k++){
		for(int l = 1; l <= N; l++){
			TYPE_SUM a = 0;
			if(x+k <= A.getN() && y+l <= A.getM()) a = A(x+k,y+l).toTypeSum();
			Res(k,l) = a;
		}
	}
}


template <class T1, class T2, class T3> void CalculatorNaiveMult2(IMatrix<T1>& Res, const IMatrix<T2>& A, const IMatrix<T3>& B) {
	// Vérifications
	if(!(A.getN() == B.getM()
		 && Res.getM() == A.getM() && Res.getN() == B.getN())) throw domain_error("produit impossible");
	Strassen(Res, A, B, pow(ceil(sqrt (A.getN())),2));

}

template <class T1, class T2, class T3> void Strassen(IMatrix<T1>& Res, const IMatrix<T2>& A, const IMatrix<T3>& B, int N) {

	if(N == 1) Res(1,1) = A(1,1).toTypeSum() * B(1,1).toTypeSum();
	else
	{
		Matrix<TYPE_SUM> M1(N/2,N/2);
		Matrix<TYPE_SUM> M2(N/2,N/2);
		Matrix<TYPE_SUM> M3(N/2,N/2);
		Matrix<TYPE_SUM> M4(N/2,N/2);
		Matrix<TYPE_SUM> M5(N/2,N/2);
		Matrix<TYPE_SUM> M6(N/2,N/2);
		Matrix<TYPE_SUM> M7(N/2,N/2);
		Matrix<TYPE_SUM> A1(N/2,N/2);
		Matrix<TYPE_SUM> B1(N/2,N/2);

		//Calcul de M1
		CalculatorNaiveSubBlock(A1,A,1,1+N/2,1+N/2,1+N/2,N/2);
		CalculatorNaiveAddBlock(B1,B,1+N/2,1,1+N/2,1+N/2,N/2);
		Strassen(M1,A1,B1,N/2);
		//Calcul de M2
		CalculatorNaiveAddBlock(A1,A,1,1,1+N/2,1+N/2,N/2);
		CalculatorNaiveAddBlock(B1,B,1,1,1+N/2,1+N/2,N/2);
		Strassen(M2,A1,B1,N/2);
		//Calcul de M3
		CalculatorNaiveSubBlock(A1,A,1,1,1+N/2,1,N/2);
		CalculatorNaiveAddBlock(B1,B,1,1,1,1+N/2,N/2);
		Strassen(M3,A1,B1,N/2);
		//Calcul de M4
		CalculatorNaiveAddBlock(A1,A,1,1,1,1+N/2,N/2);
		CalculatorNaiveCopyBlock(B1,B,1+N/2,1+N/2,N/2);
		Strassen(M4,A1,B1,N/2);
		//Calcul de M5
		CalculatorNaiveCopyBlock(A1,A,1,1,N/2);
		CalculatorNaiveSubBlock(B1,B,1,1+N/2,1+N/2,1+N/2,N/2);
		Strassen(M5,A1,B1,N/2);
		//Calcul de M6
		CalculatorNaiveCopyBlock(A1,A,1+N/2,1+N/2,N/2);
		CalculatorNaiveSubBlock(B1,B,1+N/2,1,1,1,N/2);
		Strassen(M6,A1,B1,N/2);
		//Calcul de M7
		CalculatorNaiveAddBlock(A1,A,1+N/2,1,1+N/2,1+N/2,N/2);
		CalculatorNaiveCopyBlock(B1,B,1,1,N/2);
		Strassen(M7,A1,B1,N/2);

		for(int i = 1; i <= N/2; i++){
			for(int j = 1; j <= N/2; j++){
				Res(i,j) = M1(i,j).toTypeSum() + M2(i,j).toTypeSum() - M4(i,j).toTypeSum() + M6(i,j).toTypeSum();
			}
		}
		for(int i = 1; i <= N/2; i++){
			for(int j = 1+N/2; j <= N; j++){
				Res(i,j) = M4(i,j).toTypeSum() + M5(i,j).toTypeSum();
			}
		}
		for(int i = 1+N/2; i <= N; i++){
			for(int j = 1; j <= N/2; j++){
				Res(i,j) = M6(i,j).toTypeSum() + M7(i,j).toTypeSum();
			}
		}
		for(int i = 1+N/2; i <= N; i++){
			for(int j = 1+N/2; j <= N; j++){
				Res(i,j) = M2(i,j).toTypeSum() - M3(i,j).toTypeSum() + M5(i,j).toTypeSum() - M7(i,j).toTypeSum();
			}
		}
	}
}
*/


template <class T1, class T2, class T3> void CalculatorNaiveMult(IMatrix<T1>& Res, const IMatrix<T2>& A, T3 x) {
	// Vérifications
	if(!(Res.getM() == A.getM() && Res.getN() == A.getN())) throw domain_error("produit impossible");

	for(int i = 1; i <= Res.getM(); i++){
		for(int j = 1; j<= Res.getN(); j++) {
			Res(i, j) = A(i, j).toTypeSum() * x;
		}
	}
}

template <class T1, class T2, class T3> void CalculatorNaiveAdd(IMatrix<T1>& Res, const IMatrix<T2>& A, const IMatrix<T3>& B) {
	// Vérifications
	if(!(A.getM() == B.getM() && A.getM() == Res.getM()
		 && A.getN() == B.getN() && A.getN() == Res.getN())) throw domain_error("addition impossible");

	for(int i = 1; i <= Res.getM(); i++){
		for(int j = 1; j <= Res.getN(); j++) {
			Res(i, j) = A(i, j).toTypeSum() + B(i, j).toTypeSum();
		}
	}
}
/* ----------------------------------------------------------------------- */

/* +++++++++++++++++++++++ instanciation des fonctions template pour CalculatorBlasLapack +++++++++++++++++++++++++++ */
template void CalculatorNaiveMult(IMatrix<TYPE_SUM>&, const IMatrix<TYPE_SUM>&, const IMatrix<double>&);
template void CalculatorNaiveMult(IMatrix<TYPE_SUM>&, const IMatrix<double>&, const IMatrix<TYPE_SUM>&);

template void CalculatorNaiveMult(IMatrix<TYPE_SUM>& Res, const IMatrix<TYPE_SUM>& A, double x);

template <class T1, class T2, class T3, class T4> void CalculatorNaiveLU(IMatrix<T1>& P, IMatrix<T2>& L, IMatrix<T3>& U, const IMatrix<T4>& A) {

}
template void CalculatorNaiveMult(IMatrix<TYPE_SUM>&, const IMatrix<TYPE_SUM>&, const IMatrix<TYPE_SUM>&);
/*template void CalculatorNaiveAddBlock(IMatrix<TYPE_SUM>&, const IMatrix<TYPE_SUM>&);
template void CalculatorNaiveAddBlock(IMatrix<TYPE_SUM>&, const IMatrix<double>&);
template void CalculatorNaiveSubBlock(IMatrix<TYPE_SUM>&, const IMatrix<TYPE_SUM>&);
template void CalculatorNaiveSubBlock(IMatrix<TYPE_SUM>&, const IMatrix<double>&);
template void CalculatorNaiveCopyBlock(IMatrix<TYPE_SUM>&, const IMatrix<TYPE_SUM>&);
template void CalculatorNaiveCopyBlock(IMatrix<TYPE_SUM>&, const IMatrix<double>&);
template void Strassen(IMatrix<TYPE_SUM>&, const IMatrix<TYPE_SUM>&, const IMatrix<double>&);
template void Strassen(IMatrix<TYPE_SUM>&, const IMatrix<double>&, const IMatrix<TYPE_SUM>&);
template void Strassen(IMatrix<TYPE_SUM>&, const IMatrix<TYPE_SUM>&, const IMatrix<TYPE_SUM>&);
*/
template void CalculatorNaiveAdd(IMatrix<TYPE_SUM>&, const IMatrix<TYPE_SUM>&, const IMatrix<TYPE_SUM>&);
/* ------------------------------------------------------------------------------------------------------------------ */
