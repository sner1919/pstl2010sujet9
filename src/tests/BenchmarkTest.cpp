#include "BenchmarkTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(BenchmarkTest);

void BenchmarkTest::setUp() {
}

void BenchmarkTest::tearDown() {
}

void BenchmarkTest::testPerf() {
	CalculatorNaive<PSTL_TYPE> calculator;
	ErrorGenerator<PSTL_TYPE> generator;
	pthread_t th;
	int n = 50;
	Matrix<PSTL_TYPE> A(n, n);
	Matrix<PSTL_TYPE> B(n, n);
	Matrix<PSTL_TYPE> C1(n, n);
	FullChecksumMatrix<PSTL_TYPE> C1f(C1);
	Matrix<PSTL_TYPE> C2(n, n);
	FullChecksumMatrix<PSTL_TYPE> C2f(C2);
	struct timeval start, end;

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++) A(i, j) = B(i, j) = rand();
	}

	// produit matriciel
	gettimeofday(&start, NULL);
	ColumnChecksumMatrix<PSTL_TYPE> Ac(A);
	RowChecksumMatrix<PSTL_TYPE> Br(B);
	calculator.mult(C1f, Ac, Br);
	gettimeofday(&end, NULL);
	cout << endl << "durée produit matriciel (en secondes) : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;

	CPPUNIT_ASSERT(!(C1f == C2f));
	for(int i = 1; i <= n + 1; i++){
		for(int j = 1; j <= n + 1; j++) C2f(i, j) = C1f(i, j);
	}

	// correction 0 erreurs
	CPPUNIT_ASSERT(C1f == C2f);
	gettimeofday(&start, NULL);
	C1f.errorCorrection();
	gettimeofday(&end, NULL);
	cout << "durée correction 0 erreurs (en secondes) : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
	CPPUNIT_ASSERT(C1f == C2f);

	// correction 1 erreurs
	th = generator.generateError(C1f, 1, 1, n, 1, n);
	pthread_join(th, NULL);
	CPPUNIT_ASSERT(!(C1f == C2f));
	gettimeofday(&start, NULL);
	C1f.errorCorrection();
	gettimeofday(&end, NULL);
	cout << "durée correction 1 erreurs (en secondes) : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
	CPPUNIT_ASSERT(C1f == C2f);

	// correction 2 erreurs (même ligne)
	th = generator.generateError(C1f, 2, 1, 1, 1, n);
	pthread_join(th, NULL);
	CPPUNIT_ASSERT(!(C1f == C2f));
	gettimeofday(&start, NULL);
	C1f.errorCorrection();
	gettimeofday(&end, NULL);
	cout << "durée correction 2 erreurs (en secondes) : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
	CPPUNIT_ASSERT(C1f == C2f);

}
