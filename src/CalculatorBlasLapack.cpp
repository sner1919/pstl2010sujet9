#include "CalculatorBlasLapack.hpp"
#include "interfaces/IFullChecksumMatrix.hpp"
#include <sys/time.h>
#include <typeinfo>

double dgemm, calculChecksums;

template <class T>
CalculatorBlasLapack<T>::CalculatorBlasLapack(IBlasLapackAdapter& blasLapackAdapter, int MatrixType) : blasLapackAdapter(blasLapackAdapter), MatrixType(MatrixType) {
	if(MatrixType == 1 && typeid(T) != typeid(double)) throw domain_error("le type 1 n'est compatible qu'avec les matrices de double");
}

template <class T>
void CalculatorBlasLapack<T>::mult(IMatrix<T>& Res, const IMatrix<T>& A, const IMatrix<T>& B) const {
	// Vérifications
	if(!(A.getN() == B.getM()
		 && Res.getM() == A.getM() && Res.getN() == B.getN())) throw domain_error("produit impossible");

	struct timeval start, end;
	double *res, *a, *b;

	try {

		IFullChecksumMatrix<T>& Resf = dynamic_cast<IFullChecksumMatrix<T>&>(Res);
		const IColumnChecksumMatrix<T>& Ac = dynamic_cast<const IColumnChecksumMatrix<T>&>(A);
		const IRowChecksumMatrix<T>& Br = dynamic_cast<const IRowChecksumMatrix<T>&>(B);

		cout << endl << "+++++++++++++++++++++++++++ Avec extension +++++++++++++++++++++++++++++" << endl;
		if(MatrixType == 0) {
			gettimeofday(&start, NULL);
			res = new double[(Resf.getM() - 1) * (Resf.getN() - 1)];
			a = new double[(Ac.getM() - 1) * Ac.getN()];
			b = new double[Br.getM() * (Br.getN() - 1)];
			gettimeofday(&end, NULL);
			cout << endl << "	- alloc : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

			gettimeofday(&start, NULL);
			Ac.getColumnMatrix().toDouble(a, true);
			Br.getRowMatrix().toDouble(b, true);
			gettimeofday(&end, NULL);
			cout << "	- toDouble : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
		} else {
			a = Ac.getColumnMatrix().getData();
			b = Br.getRowMatrix().getData();
			res = Resf.getRowMatrix().getData();
		}

		gettimeofday(&start, NULL);
		blasLapackAdapter.dgemm(CblasRowMajor_, CblasNoTrans_, CblasNoTrans_,
			Ac.getM() - 1, Br.getN() - 1, Ac.getN(),
			1., a, Ac.getN(),
			b, Br.getN() - 1,
			0., res, Resf.getN() - 1);
		gettimeofday(&end, NULL);
		dgemm = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
		cout << "	- dgemm : " << dgemm << endl;


		if(MatrixType == 0) {
			gettimeofday(&start, NULL);
			Resf.getRowMatrix().fromDouble(res, true);
			gettimeofday(&end, NULL);
			cout << "	- fromDouble : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
		}

		gettimeofday(&start, NULL);
		CalculatorNaiveMult<TYPE_SUM, TYPE_SUM, T>(Resf.getColumnSummationVector(), Ac.getColumnSummationVector(), Br);
		CalculatorNaiveMult<TYPE_SUM, T, TYPE_SUM>(Resf.getRowSummationVector(), Ac.getColumnMatrix(), Br.getRowSummationVector());
		gettimeofday(&end, NULL);
		calculChecksums = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
		cout << "	- CalculatorNaiveMult : " << calculChecksums << endl;

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
			A.toDouble(a, true);
			B.toDouble(b, true);
			gettimeofday(&end, NULL);
			cout << "	- toDouble : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
		} else {
			a = A.getData();
			b = B.getData();
			res = Res.getData();
		}

		gettimeofday(&start, NULL);
		blasLapackAdapter.dgemm(CblasRowMajor_, CblasNoTrans_, CblasNoTrans_,
			A.getM(), B.getN(), A.getN(),
			1., (const double *) a, A.getN(),
			(const double *) b, B.getN(),
			0., res, Res.getN());
		gettimeofday(&end, NULL);
		cout << "	- dgemm : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

		if(MatrixType == 0) {
			gettimeofday(&start, NULL);
			Res.fromDouble(res, true);
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

			Af.getRowMatrix().toDouble(res, true);
		} else {
			res = Resf.getRowMatrix().getData();

			copy(Af.getRowMatrix().getData(), Af.getRowMatrix().getData() + (Resf.getM() - 1) * (Resf.getN() - 1), res);
		}

		blasLapackAdapter.dscal((Resf.getM() - 1) * (Resf.getN() - 1), x, res, 1);

		if(MatrixType == 0) {
			Resf.getRowMatrix().fromDouble(res, true);
		}

		CalculatorNaiveMult<TYPE_SUM, TYPE_SUM, T>(Resf.getColumnSummationVector(), Af.getColumnSummationVector(), x);
		CalculatorNaiveMult<TYPE_SUM, TYPE_SUM, T>(Resf.getRowSummationVector(), Af.getRowSummationVector(), x);

	} catch (bad_cast) {

		if(MatrixType == 0) {
			res = new double[Res.getM() * Res.getN()];

			A.toDouble(res, true);
		} else {
			res = Res.getData();

			copy(A.getData(), A.getData() + Res.getM() * Res.getN(), res);
		}

		blasLapackAdapter.dscal(Res.getM() * Res.getN(), x, res, 1);

		if(MatrixType == 0) {
			Res.fromDouble(res, true);
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

			Bf.getRowMatrix().toDouble(res, true);
			Af.getRowMatrix().toDouble(a, true);
		} else {
			res = Resf.getRowMatrix().getData();
			a = Af.getRowMatrix().getData();

			copy(Bf.getRowMatrix().getData(), Bf.getRowMatrix().getData() + (Resf.getM() - 1) * (Resf.getN() - 1), res);
		}

		blasLapackAdapter.daxpy((Resf.getM() - 1) * (Resf.getN() - 1), 1, a, 1, res, 1);

		if(MatrixType == 0) {
			Resf.getRowMatrix().fromDouble(res, true);
		}

		CalculatorNaiveAdd<TYPE_SUM, TYPE_SUM, TYPE_SUM>(Resf.getColumnSummationVector(), Af.getColumnSummationVector(), Bf.getColumnSummationVector());
		CalculatorNaiveAdd<TYPE_SUM, TYPE_SUM, TYPE_SUM>(Resf.getRowSummationVector(), Af.getRowSummationVector(), Bf.getRowSummationVector());

	} catch (bad_cast) {

		if(MatrixType == 0) {
			res = new double[Res.getM() * Res.getN()];
			a = new double[A.getM() * A.getN()];

			B.toDouble(res, true);
			A.toDouble(a, true);
		} else {
			res = Res.getData();
			a = A.getData();

			copy(B.getData(), B.getData() + Res.getM() * Res.getN(), res);
		}

		blasLapackAdapter.daxpy(Res.getM() * Res.getN(), 1, a, 1, res, 1);

		if(MatrixType == 0) {
			Res.fromDouble(res, true);
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
