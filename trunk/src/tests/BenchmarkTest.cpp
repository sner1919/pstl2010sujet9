#include "BenchmarkTest.hpp"
#include "../FullChecksumMatrix.hpp"
#include "../CalculatorNaive.hpp"
#include "../CalculatorBlasLapack.hpp"
#include "../AtlasAdapter.hpp"
#include "../GotoBlasAdapter.hpp"
#include "../IntelMKLAdapter.hpp"
#include "../ErrorGenerator.hpp"
#include <cmath>
#include <cstdlib>
#include <sys/time.h>
#include <limits>

CPPUNIT_TEST_SUITE_REGISTRATION(BenchmarkTest);

void BenchmarkTest::setUp() {
}

void BenchmarkTest::tearDown() {
}

void BenchmarkTest::testPerf() {
	CalculatorNaive<double> calculatorNaive;
	AtlasAdapter atlasAdapter;
	GotoBlasAdapter gotoBlasAdapter;
	IntelMKLAdapter intelMKLAdapter;
	CalculatorBlasLapack<double> calculatorAtlas(atlasAdapter, 1);
	CalculatorBlasLapack<double> calculatorGotoBlas(gotoBlasAdapter, 1);
	CalculatorBlasLapack<double> calculatorIntelMKL(intelMKLAdapter, 1);
	ErrorGenerator<double> generator;
	pthread_t th;
	int n = 100;
	Matrix<double> A(n, n);
	Matrix<double> B(n, n);
	Matrix<double> C1(n, n);
	FullChecksumMatrix<double> C1f(C1);
	Matrix<double> C2(n, n);
	FullChecksumMatrix<double> C2f(C2);
	struct timeval start, end;
	double extensionTime;

	/*
	 * Soit A * B = C, avec A et B des matrices de taille N * N;
	 * Pour que les valeur de C soient <= MaxDouble, il faut que max(A) * max(B) * N <= MaxDouble.
	 * Cad. max(A, B) <= sqrt(MaxDouble / N)
	 */
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++) {
			A(i, j) = fmod(((float) rand() / (float) RAND_MAX - 0.5) * 2 * numeric_limits<double>::max(), sqrt(numeric_limits<double>::max() / n));
			B(i, j) = fmod(((float) rand() / (float) RAND_MAX - 0.5) * 2 * numeric_limits<double>::max(), sqrt(numeric_limits<double>::max() / n));
		}
	}

	cout << endl << "Benchmark : matrice " << n << " x " << n << endl;

	// produit matriciel
	cout << "durée produit matriciel (en secondes) : " << endl;

	gettimeofday(&start, NULL);
	ColumnChecksumMatrix<double> Ac(A);
	RowChecksumMatrix<double> Br(B);
	gettimeofday(&end, NULL);
	extensionTime = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;

	if(n <= 500) {
		/*cout << "C1f.getColumnSummationVector()(1).toTypeSum().get_prec() : " << C1f.getColumnSummationVector()(1).toTypeSum().get_prec() << endl;
		cout << "Ac : " << Ac.toString() << endl;
		cout << "Br : " << Br.toString() << endl;
		cout << "C1f : " << C1f.toString() << endl;
		cout << "C1f.computeRowSum(1) : " << C1f.computeRowSum(1) << endl;
		cout << "C1f.computeRowSum(2) : " << C1f.computeRowSum(2) << endl;*/
		gettimeofday(&start, NULL);
		calculatorNaive.mult(C1f, Ac, Br);
		gettimeofday(&end, NULL);
		/*cout << "	- Naïf : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
		cout << "Ac : " << Ac.toString() << endl;
		cout << "Br : " << Br.toString() << endl;
		cout << "C1f : " << C1f.toString() << endl;
		cout << "C1f.computeRowSum(1) : " << C1f.computeRowSum(1) << endl;
		cout << "C1f.computeRowSum(2) : " << C1f.computeRowSum(2) << endl;*/
		CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
		for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= n + 1 ; j++) C1f(i, j) = 0;
	}

	gettimeofday(&start, NULL);
	calculatorAtlas.mult(C1f, Ac, Br);
	gettimeofday(&end, NULL);
	cout << "	- Atlas : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
	CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
	for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= n + 1 ; j++) C1f(i, j) = 0;

	gettimeofday(&start, NULL);
	calculatorAtlas.mult(C1f, Ac, Br);
	gettimeofday(&end, NULL);
	cout << "	- Atlas : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
	CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
	for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= n + 1 ; j++) C1f(i, j) = 0;

	gettimeofday(&start, NULL);
	calculatorAtlas.mult(C1f, Ac, Br);
	gettimeofday(&end, NULL);
	cout << "	- Atlas : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
	CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
	for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= n + 1 ; j++) C1f(i, j) = 0;

	gettimeofday(&start, NULL);
	calculatorGotoBlas.mult(C1f, Ac, Br);
	gettimeofday(&end, NULL);
	cout << "	- GotoBlas : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
	CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
	for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= n + 1 ; j++) C1f(i, j) = 0;

	gettimeofday(&start, NULL);
	calculatorGotoBlas.mult(C1f, Ac, Br);
	gettimeofday(&end, NULL);
	cout << "	- GotoBlas : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
	CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
	for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= n + 1 ; j++) C1f(i, j) = 0;

	gettimeofday(&start, NULL);
	calculatorGotoBlas.mult(C1f, Ac, Br);
	gettimeofday(&end, NULL);
	cout << "	- GotoBlas : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
	CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
	for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= n + 1 ; j++) C1f(i, j) = 0;

	gettimeofday(&start, NULL);
	calculatorIntelMKL.mult(C1f, Ac, Br);
	gettimeofday(&end, NULL);
	CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
	cout << "	- IntelMKL : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

	gettimeofday(&start, NULL);
	calculatorIntelMKL.mult(C1f, Ac, Br);
	gettimeofday(&end, NULL);
	CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
	cout << "	- IntelMKL : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

	gettimeofday(&start, NULL);
	calculatorIntelMKL.mult(C1f, Ac, Br);
	gettimeofday(&end, NULL);
	CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
	cout << "	- IntelMKL : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

	CPPUNIT_ASSERT(!(C1f == C2f));
	(IMatrix<double>&) C2f = C1f;

	// correction 0 erreurs
	CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
	CPPUNIT_ASSERT(C1f == C2f);
	gettimeofday(&start, NULL);
	C1f.errorCorrection();
	gettimeofday(&end, NULL);
	cout << "durée extension + correction 0 erreurs (en secondes) : " << extensionTime + (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
	CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
	CPPUNIT_ASSERT(C1f == C2f);

	// correction 1 erreurs
	th = generator.generateError(C1f, 1, 1, n + 1, 1, n + 1);
	pthread_join(th, NULL);
	CPPUNIT_ASSERT(C1f.columnErrorDetection() && C1f.rowErrorDetection());
	CPPUNIT_ASSERT(!(C1f == C2f));
	gettimeofday(&start, NULL);
	C1f.errorCorrection();
	gettimeofday(&end, NULL);
	cout << "durée extension + correction 1 erreurs (en secondes) : " << extensionTime + (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
	CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
	CPPUNIT_ASSERT(C1f == C2f);

	// correction 2 erreurs (même ligne)
	th = generator.generateError(C1f, 2, 1, 1, 1, n + 1);
	pthread_join(th, NULL);
	CPPUNIT_ASSERT(C1f.columnErrorDetection() && C1f.rowErrorDetection());
	CPPUNIT_ASSERT(!(C1f == C2f));
	gettimeofday(&start, NULL);
	C1f.errorCorrection();
	gettimeofday(&end, NULL);
	cout << "durée extension + correction 2 erreurs (en secondes) : " << extensionTime + (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
	CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
	CPPUNIT_ASSERT(C1f == C2f);

}
