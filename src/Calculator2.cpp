#include "ICalculator.hpp"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include "/home/moi/numerics/ATLAS3.8.0/include/clapack.h"
#include "/home/moi/numerics/ATLAS3.8.0/include/cblas.h"


template <class T> class Calculator2 : public ICalculator<T> {
	public:
		int* ipvt;
		int info;


		void mult(IMatrix<T>& Res, IMatrix<T>& A, IMatrix<T>& B){
			if(!(A.getN() == B.getM()
							 && Res.getM() == A.getM() && Res.getN() == B.getN())) throw domain_error("produit impossible");
			cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
					A.getM(), B.getN(), A.getN(), 1.0, A.getData(), A.getM(),
					B.getData(), B.getM(), 1.0, Res.getData(), Res.getM());
		}

		void mult(IMatrix<T>& Res,IMatrix<T>& A, T x){
			// Vérifications
			if(!(Res.getM() == A.getM() && Res.getN() == A.getN())) throw domain_error("produit impossible");

			cblas_dgemv(CblasColMajor, CblasNoTrans,A.getM(),A.getN(),
					1.0,A.getData(),A.getM(),&x,0,0.0,Res.getData(),0);
		}

		void add(IMatrix<T>& Res,IMatrix<T>& A, IMatrix<T>& B){
			dgeadd_(A.getData(),A.getM(),CblasNoTrans,B.getData(),B.getM(),
					CblasNoTrans,Res.getData(),Res.getM(),Res.getM(),Res.getN());
		}

		void transpose(IMatrix<T>& Res, IMatrix<T>& A){
			// Vérifications
			if(!(A.getM() == Res.getN() && A.getN() == Res.getM()))  throw domain_error("transposition impossible");

			cblas_dgemv(CblasColMajor, CblasTrans,A.getM(),A.getN(),
					1.0,A.getData(),A.getM(),1.,0,0.0,Res.getData(),0);
		}

		// Hypothèse la matrice A est LU décomposable
		void LU(IMatrix<T>& L, IMatrix<T>& U, IMatrix<T>& A){
			// Vérifications
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
						L(i,j) == 1;
					}
					else
					{
						L(i,j) = 0;
					}
				}
			}


		}
};
