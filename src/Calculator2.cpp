#include "Calculator2.hpp"

template <class T>
void Calculator2<T>::mult(IMatrix<T>& Res, IMatrix<T>& A, IMatrix<T>& B){
	if(!(A.getN() == B.getM()
					 && Res.getM() == A.getM() && Res.getN() == B.getN())) throw domain_error("produit impossible");
	cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
			B.getM(), A.getN(), B.getN(), 1.0, B.getData(), B.getM(),
			A.getData(), A.getM(), 0.0, Res.getData(), Res.getM());
}

template <class T>
void Calculator2<T>::mult(IMatrix<T>& Res,IMatrix<T>& A, T x){
	// Vérifications
	if(!(Res.getM() == A.getM() && Res.getN() == A.getN())) throw domain_error("produit impossible");

	cblas_dgemv(CblasRowMajor, CblasNoTrans,A.getM(),A.getN(),
			1.0,A.getData(),A.getM(),&x,1,0.0,Res.getData(),1);
}

template <class T>
void Calculator2<T>::add(IMatrix<T>& Res,IMatrix<T>& A, IMatrix<T>& B){
	//dgeadd_(A.getData(),A.getM(),CblasNoTrans,B.getData(),B.getM(),
		//	CblasNoTrans,Res.getData(),Res.getM(),Res.getM(),Res.getN());
	for(int i = 1; i <= Res.getM(); i++){
			for(int j = 1; j <= Res.getN(); j++){
				Res(i, j) = 0.;
				Res(i, j) = A(i, j) + B(i, j);
			}
		}
}

template <class T>
void Calculator2<T>::transpose(IMatrix<T>& Res, IMatrix<T>& A){
	// Vérifications
	if(!(A.getM() == Res.getN() && A.getN() == Res.getM()))  throw domain_error("transposition impossible");

	const double x = 1.;
	cblas_dgemv(CblasColMajor, CblasTrans,A.getM(),A.getN(),
			1.0,A.getData(),A.getM(),&x,1,0.0,Res.getData(),1);
}

// Hypothèse la matrice A est LU décomposable
template <class T>
void Calculator2<T>::LU(IMatrix<T>& L, IMatrix<T>& U, IMatrix<T>& A){
	/*// Vérifications
	if(!(A.getM() == A.getN()
		 && A.getM() == L.getM() && A.getM() == L.getN()
		 && A.getM() == U.getM() && A.getM() == U.getN()))  throw domain_error("décomposition LU impossible");
	ipvt = new int[A.getM()];
	mult(U,A,1.);
	clapack_dgetrf(U.getM(),U.getN(),U.getData(),U.getM(),&ipvt, &info);
	for(int i= 0;i < U.getM(); i++){
		for(int j=0; j < U.getN(); j++){
			if(i < j){
				L(i,j) = U(i,j);
				U(i,j) = 0;
			}
			else if(i == j){
				L(i,j) = 1;
			}
			else
			{
				L(i,j) = 0;
			}
		}
	}*/
	// Vérifications
		if(!(A.getM() == A.getN()
			 && A.getM() == L.getM() && A.getM() == L.getN()
			 && A.getM() == U.getM() && A.getM() == U.getN()))  throw domain_error("décomposition LU impossible");

		T** c = new T*[A.getM()];
		for(int i = 1; i <= A.getM(); i++){
			c[i-1] = new T[A.getM()];
			for(int j = 1; j <= A.getM(); j++) c[i-1][j-1] = A(i, j);
		}

		for(int k = 1; k <= A.getM(); k++){
			for(int i = 1; i <= A.getM(); i++){
				if(k > i) U(k, i) = 0;
				else U(k, i) = c[k-1][i-1];

				if(i < k) L(i, k) = 0;
				else if(i == k) L(i, k) = 1;
				else L(i, k) = c[i-1][k-1] * (1 / U(k, k));

				for(int j = 1; j <= A.getM(); j++) c[i-1][j-1] = c[i-1][j-1] + L(i, k) * -U(k, j);
			}
		}

		// liberation de la mémoire
		for(int i = 0; i < A.getM(); i++) delete [] c[i];
		delete [] c;
}

template class Calculator2<double>;
