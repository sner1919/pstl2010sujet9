#include "ICalculator.hpp"
#include <sstream>
#include <stdexcept>

template <class T> class Calculator : public ICalculator<T> {
	public:
		void mult(IMatrix<T>& Res, IMatrix<T>& A, IMatrix<T>& B){
			// Vérifications
			if(!(A.getN() == B.getM()
				 && Res.getM() == A.getM() && Res.getN() == B.getN())) throw domain_error("produit impossible");

			for(int i = 0; i < Res.getM(); i++){
				for(int j = 0; j < Res.getN(); j++){
					Res(i, j) = 0.;
					for(int k = 0; k < Res.getN(); k++) Res(i, j) = Res(i, j) + A(i, k) * B(k, j);
				}
			}
		}

		void mult(IMatrix<T>& Res,IMatrix<T>& A, T x){
			// Vérifications
			if(!(Res.getM() == A.getM() && Res.getN() == A.getN())) throw domain_error("produit impossible");

			for(int i = 0; i < Res.getM(); i++){
				for(int j = 0; j < Res.getN(); j++){
					Res(i, j) = A(i, j) * x;
				}
			}
		}

		void add(IMatrix<T>& Res,IMatrix<T>& A, IMatrix<T>& B){
			// Vérifications
			if(!(A.getM() == B.getM() && A.getM() == Res.getM()
				 && A.getN() == B.getN() && A.getN() == Res.getN()))  throw domain_error("addition impossible");

			for(int i = 0; i < Res.getM(); i++){
				for(int j = 0; j < Res.getN(); j++){
					Res(i, j) = 0.;
					Res(i, j) = A(i, j) + B(i, j);
				}
			}
		}

		void transpose(IMatrix<T>& Res, IMatrix<T>& A){
			// Vérifications
			if(!(A.getM() == Res.getN() && A.getN() == Res.getM()))  throw domain_error("transposition impossible");

			for(int i = 0; i < Res.getM(); i++){
				for(int j = 0; j < Res.getN(); j++){
					Res(j, i) = A(i, j);
				}
			}
		}

		// Hypothèse la matrice *this est LU décomposable
		void LU(IMatrix<T>& L, IMatrix<T>& U, IMatrix<T>& A){
			// Vérifications
			if(!(A.getM() == A.getN()
				 && A.getM() == L.getM() && A.getM() == L.getN()
				 && A.getM() == U.getM() && A.getM() == U.getN()))  throw domain_error("décomposition LU impossible");

			T** c = new T*[A.getM()];
			for(int i = 0; i < A.getM(); i++){
				c[i] = new T[A.getM()];
				for(int j = 0; j < A.getM(); j++) c[i][j] = A(i, j);
			}

			for(int k = 0; k < A.getM(); k++){
				for(int i = 0; i < A.getM(); i++){
					if(k > i) U(k, i) = 0;
					else U(k, i) = c[k][i];

					if(i < k) L(i, k) = 0;
					else if(i == k) L(i, k) = 1;
					else L(i, k) = c[i][k] * (1 / U(k, k));

					for(int j = 0; j < A.getM(); j++) c[i][j] = c[i][j] + L(i, k) * -U(k, j);
				}
			}
		}
};
