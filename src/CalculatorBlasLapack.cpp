#include "CalculatorBlasLapack.hpp"
#include "interfaces/IFullChecksumMatrix.hpp"
#include <sys/time.h>
#include <typeinfo>
#include "../include/mpack/mblas_gmp.h"
#include "../include/mpack/mlapack_gmp.h"

double dgemm, calculChecksums, calculChecksumsMPack;

template <class T>
CalculatorBlasLapack<T>::CalculatorBlasLapack(IBlasLapackAdapter& blasLapackAdapter, int MatrixType) : blasLapackAdapter(blasLapackAdapter), MatrixType(MatrixType) {
	if(MatrixType == 1 && typeid(T) != typeid(double)) throw domain_error("le type 1 n'est compatible qu'avec les matrices de double");
}

template <class T>
void CalculatorBlasLapack<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
 	// Vérifications
	if(!(A.getN() == B.getM()
		 && Res.getM() == A.getM() && Res.getN() == B.getN())) throw domain_error("produit impossible");

	struct timeval start, start2, end;

	double *res, *a, *b;

	try {

		IFullChecksumMatrix<T>& Resf = dynamic_cast<IFullChecksumMatrix<T>&>(Res);
		const IColumnChecksumMatrix<T>& Ac = dynamic_cast<const IColumnChecksumMatrix<T>&>(A);
		const IRowChecksumMatrix<T>& Br = dynamic_cast<const IRowChecksumMatrix<T>&>(B);

		cout << endl << "+++++++++++++++++++++++++++ Avec extension +++++++++++++++++++++++++++++" << endl;

		/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++ Produit Hybride +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

		if(MatrixType == 0) {
			gettimeofday(&start, NULL);
			res = new double[(Resf.getM() - 1) * (Resf.getN() - 1)];
			a = new double[(Ac.getM() - 1) * Ac.getN()];
			b = new double[Br.getM() * (Br.getN() - 1)];
			gettimeofday(&end, NULL);
			cout << endl << "	- alloc : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

			gettimeofday(&start, NULL);
			Ac.getColumnMatrix().toDouble(a, false);
			Br.getRowMatrix().toDouble(b, false);
			gettimeofday(&end, NULL);
			cout << "	- toDouble : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
		} else {
			a = Ac.getColumnMatrix().getData();
			b = Br.getRowMatrix().getData();
			res = Resf.getRowMatrix().getData();
		}

		gettimeofday(&start, NULL);
		/*blasLapackAdapter.dgemm(CblasColMajor_, CblasNoTrans_, CblasNoTrans_,
			Ac.getM() - 1, Br.getN() - 1, Ac.getN(),
			1., a, Ac.getM() - 1,
			b, Br.getM(),
			0., res, Resf.getM() - 1);*/
		gettimeofday(&end, NULL);
		dgemm = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
		cout << "	- dgemm : " << dgemm << endl;


		if(MatrixType == 0) {
			gettimeofday(&start, NULL);
			Resf.getRowMatrix().fromDouble(res, false);
			gettimeofday(&end, NULL);
			cout << "	- fromDouble : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
		}

		gettimeofday(&start2, NULL);

		/* ++++++++++++++++++ utilisation du calculateur Naïf +++++++++++++++ */
		//CalculatorNaiveMult<double, double, T>(Resf.getColumnSummationVector(), Ac.getColumnSummationVector(), Br);
		//CalculatorNaiveMult<double, T, double>(Resf.getRowSummationVector(), Ac.getColumnMatrix(), Br.getRowSummationVector());
		gettimeofday(&end, NULL);
		calculChecksums = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
		cout << "	- calculChecksums : " << calculChecksums << endl;
		/* ------------------------------------------------------------------ */

		/* ++++++++++++++++++ utilisation de MPack +++++++++++++++ */
		/* ++++++++++++++++++ Resf.getColumnSummationVector() +++++++++++++++ */
		/*mpf_set_default_prec(64);
		mpf_class *res, *a, *x;

		gettimeofday(&start, NULL);
		res = new mpf_class[Resf.getN()];
		x = new mpf_class[Ac.getN()];
		a = new mpf_class[Br.getM() * Br.getN()];
		gettimeofday(&end, NULL);
		cout << "	- alloc : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

		gettimeofday(&start, NULL);
		Ac.getColumnSummationVector().toTypeSum(x, false);
		Br.toTypeSum(a, false);
		gettimeofday(&end, NULL);
		cout << "	- toTypeSum : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

		gettimeofday(&start, NULL);
		Rgemv("Transpose", (mpackint) Br.getM(), (mpackint) Br.getN(), (mpf_class) 1.,
			 a, (mpackint) Br.getM(), x, (mpackint) 1,
			 (mpf_class) 0., res, (mpackint) 1);
		gettimeofday(&end, NULL);
		cout << "	- Rgemv : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

		gettimeofday(&start, NULL);
		Resf.getColumnSummationVector().fromTypeSum(res, false);
		gettimeofday(&end, NULL);
		cout << "	- fromTypeSum : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

		delete [] res; delete [] a; delete [] x;*/

		/* ++++++++++++++++++ Resf.getRowSummationVector() +++++++++++++++ */

		/*gettimeofday(&start, NULL);
		res = new mpf_class[Resf.getM() - 1];
		a = new mpf_class[Ac.getColumnMatrix().getM() * Ac.getColumnMatrix().getN()];
		x = new mpf_class[Br.getM()];
		gettimeofday(&end, NULL);
		cout << "	- alloc : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

		gettimeofday(&start, NULL);
		Ac.getColumnMatrix().toTypeSum(a, false);
		Br.getRowSummationVector().toTypeSum(x, false);
		gettimeofday(&end, NULL);
		cout << "	- toTypeSum : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

		gettimeofday(&start, NULL);
		Rgemv("NoTranspose", (mpackint) Ac.getColumnMatrix().getM(), (mpackint) Ac.getColumnMatrix().getN(), (mpf_class) 1.,
			 a, (mpackint) Ac.getColumnMatrix().getM(), x, (mpackint) 1,
			 (mpf_class) 0., res, (mpackint) 1);
		gettimeofday(&end, NULL);
		cout << "	- Rgemv : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

		gettimeofday(&start, NULL);
		Resf.getRowSummationVector().fromTypeSum(res, false);
		gettimeofday(&end, NULL);
		cout << "	- fromTypeSum : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

		delete [] res; delete [] a; delete [] x;*/
		/* ------------------------------------------------------- */

		/*gettimeofday(&end, NULL);
		calculChecksumsMPack = end.tv_sec - start2.tv_sec + (end.tv_usec - start2.tv_usec) / 1000000.0;
		cout << "	- calculChecksumsMPack : " << calculChecksumsMPack << endl;*/
		/* ----------------------------------------------------------------------------------------------------------------------------------------- */

	} catch (bad_cast) {

		cout << endl << "+++++++++++++++++++++++++++ Sans extension +++++++++++++++++++++++++++++" << endl;
		if(MatrixType == 0) {
			gettimeofday(&start, NULL);
			res = new double[Res.getM() * Res.getN()];
			a = new double[A.getM() * A.getN()];
			b = new double[B.getM() * B.getN()];
			gettimeofday(&end, NULL);
			cout << endl << "	- alloc : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

			gettimeofday(&start, NULL);
			A.toDouble(a, false);
			B.toDouble(b, false);
			gettimeofday(&end, NULL);
			cout << "	- toDouble : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
		} else {
			a = A.getData();
			b = B.getData();
			res = Res.getData();
		}

		gettimeofday(&start, NULL);
		blasLapackAdapter.dgemm(CblasColMajor_, CblasNoTrans_, CblasNoTrans_,
			A.getM(), B.getN(), A.getN(),
			1., (const double *) a, A.getM(),
			(const double *) b, B.getM(),
			0., res, Res.getM());
		gettimeofday(&end, NULL);
		cout << "	- dgemm : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

		if(MatrixType == 0) {
			gettimeofday(&start, NULL);
			Res.fromDouble(res, false);
			gettimeofday(&end, NULL);
			cout << "	- fromDouble : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
		}

	}

	if(MatrixType == 0) {
		gettimeofday(&start, NULL);
		delete [] res; delete [] a; delete [] b;
		gettimeofday(&end, NULL);
		cout << "	- delete : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
	}
}

template <class T>
void CalculatorBlasLapack<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, T x) const {
	// Vérifications
	if(!(Res.getM() == A.getM() && Res.getN() == A.getN())) throw domain_error("produit impossible");

	double *res;

	try {

		IFullChecksumMatrix<T>& Resf = dynamic_cast<IFullChecksumMatrix<T>&>(Res);
		const IFullChecksumMatrix<T>& Af = dynamic_cast<const IFullChecksumMatrix<T>&>(A);

		if(MatrixType == 0) {
			res = new double[(Resf.getM() - 1) * (Resf.getN() - 1)];

			Af.getRowMatrix().toDouble(res, false);
		} else {
			res = Resf.getRowMatrix().getData();

			copy(Af.getRowMatrix().getData(), Af.getRowMatrix().getData() + (Resf.getM() - 1) * (Resf.getN() - 1), res);
		}

		blasLapackAdapter.dscal((Resf.getM() - 1) * (Resf.getN() - 1), x, res, 1);

		if(MatrixType == 0) {
			Resf.getRowMatrix().fromDouble(res, false);
		}

		CalculatorNaiveMult<double, double, T>(Resf.getColumnSummationVector(), Af.getColumnSummationVector(), x);
		CalculatorNaiveMult<double, double, T>(Resf.getRowSummationVector(), Af.getRowSummationVector(), x);

	} catch (bad_cast) {

		if(MatrixType == 0) {
			res = new double[Res.getM() * Res.getN()];

			A.toDouble(res, false);
		} else {
			res = Res.getData();

			copy(A.getData(), A.getData() + Res.getM() * Res.getN(), res);
		}

		blasLapackAdapter.dscal(Res.getM() * Res.getN(), x, res, 1);

		if(MatrixType == 0) {
			Res.fromDouble(res, false);
		}

	}

	if(MatrixType == 0) {
		delete [] res;
	}
}

template <class T>
void CalculatorBlasLapack<T>::add(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	// Vérifications
	if(!(A.getM() == B.getM() && A.getM() == Res.getM()
		 && A.getN() == B.getN() && A.getN() == Res.getN())) throw domain_error("addition impossible");

	double *res, *a;

	try {

		IFullChecksumMatrix<T>& Resf = dynamic_cast<IFullChecksumMatrix<T>&>(Res);
		const IFullChecksumMatrix<T>& Af = dynamic_cast<const IFullChecksumMatrix<T>&>(A);
		const IFullChecksumMatrix<T>& Bf = dynamic_cast<const IFullChecksumMatrix<T>&>(B);

		if(MatrixType == 0) {
			res = new double[(Resf.getM() - 1) * (Resf.getN() - 1)];
			a = new double[(Af.getM() - 1) * (Af.getN() - 1)];

			Bf.getRowMatrix().toDouble(res, false);
			Af.getRowMatrix().toDouble(a, false);
		} else {
			res = Resf.getRowMatrix().getData();
			a = Af.getRowMatrix().getData();

			copy(Bf.getRowMatrix().getData(), Bf.getRowMatrix().getData() + (Resf.getM() - 1) * (Resf.getN() - 1), res);
		}

		blasLapackAdapter.daxpy((Resf.getM() - 1) * (Resf.getN() - 1), 1, a, 1, res, 1);

		if(MatrixType == 0) {
			Resf.getRowMatrix().fromDouble(res, false);
		}

		CalculatorNaiveAdd<double, double, double>(Resf.getColumnSummationVector(), Af.getColumnSummationVector(), Bf.getColumnSummationVector());
		CalculatorNaiveAdd<double, double, double>(Resf.getRowSummationVector(), Af.getRowSummationVector(), Bf.getRowSummationVector());

	} catch (bad_cast) {

		if(MatrixType == 0) {
			res = new double[Res.getM() * Res.getN()];
			a = new double[A.getM() * A.getN()];

			B.toDouble(res, false);
			A.toDouble(a, false);
		} else {
			res = Res.getData();
			a = A.getData();

			copy(B.getData(), B.getData() + Res.getM() * Res.getN(), res);
		}

		blasLapackAdapter.daxpy(Res.getM() * Res.getN(), 1, a, 1, res, 1);

		if(MatrixType == 0) {
			Res.fromDouble(res, false);
		}

	}

	if(MatrixType == 0) {
		delete [] res; delete [] a;
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

template class CalculatorBlasLapack<double>;
