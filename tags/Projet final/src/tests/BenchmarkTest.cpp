#include "BenchmarkTest.hpp"
#include "../FullChecksumMatrix.hpp"
#include "../CalculatorNaive.hpp"
#include "../CalculatorBlasLapack.hpp"
#include "../AtlasAdapter.hpp"
#include "../GotoBlasAdapter.hpp"
#include "../IntelMKLAdapter.hpp"
#include "../MPackAdapter.hpp"
#include "../ErrorGenerator.hpp"
#include <cmath>
#include <cstdlib>
#include <sys/time.h>
#include <limits>
#include <fstream>

extern double dgemm, calculChecksums, calculChecksumsMPack;

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
	MPackAdapter mPackAdapter;
	CalculatorBlasLapack<double> calculatorAtlas(atlasAdapter, 1);
	CalculatorBlasLapack<double> calculatorGotoBlas(gotoBlasAdapter, 1);
	CalculatorBlasLapack<double> calculatorIntelMKL(intelMKLAdapter, 1);
	CalculatorBlasLapack<double> calculatorMPack(mPackAdapter, 1);
	ErrorGenerator<double> generator;
	pthread_t th;
	ofstream naiveFile ("./benchmark/" MACRO_TO_STR(CPU) "Naif.data", ios::out | ios::trunc);
	ofstream atlasFile ("./benchmark/" MACRO_TO_STR(CPU) "Atlas.data", ios::out | ios::trunc);
	ofstream gotoBlasFile ("./benchmark/" MACRO_TO_STR(CPU) "GotoBlas.data", ios::out | ios::trunc);
	ofstream intelMKLFile ("./benchmark/" MACRO_TO_STR(CPU) "IntelMKL.data", ios::out | ios::trunc);
	ofstream mPackFile ("./benchmark/" MACRO_TO_STR(CPU) "MPack.data", ios::out | ios::trunc);
	ofstream calculChecksumsFile ("./benchmark/" MACRO_TO_STR(CPU) "CalculChecksums.data", ios::out | ios::trunc);
	ofstream calculChecksumsMPackFile ("./benchmark/" MACRO_TO_STR(CPU) "CalculChecksumsMPack.data", ios::out | ios::trunc);
	ofstream extensionFile ("./benchmark/" MACRO_TO_STR(CPU) "Extension.data", ios::out | ios::trunc);
	ofstream correctionFile ("./benchmark/" MACRO_TO_STR(CPU) "Correction.data", ios::out | ios::trunc);
	if(!atlasFile) cerr << "Impossible d'ouvrir le fichier !" << endl;
	int nMax = 100;


	for(int n = nMax / 10 * 9; n <= nMax; n += nMax / 10) {

		Matrix<double> A(n, n);
		Matrix<double> B(n, n);
		Matrix<double> C1(n, n);
		FullChecksumMatrix<double> C1f(C1);
		Matrix<double> C2(n, n);
		FullChecksumMatrix<double> C2f(C2);
		struct timeval start, end;
		double t;

		cout << endl << "Benchmark : matrice " << n << " x " << n << endl;

		/*
		 * Initialisation de A et B
		 *
		 * Soit A * B = C, avec A et B des matrices de taille N * N;
		 *
		 * Overflow :
		 * Pour que les valeur de C soient <= MaxDouble, il faut que max(A) * max(B) * N <= MaxDouble.
		 * Cad. max(A, B) <= sqrt(MaxDouble / N)
		 *
		 * Underflow :
		 * Pour que les valeur de C ne soient pas dans l'intervalle ]0, MinDoublePositive[, il faut que min(A) * min(B) * N >= MinDoublePositive si min(A, B) > 0.
		 * Cad. min(A, B) >= sqrt(MinDoublePositive / N)
		 */
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++) {
				double v[2];

				for(int k = 0; k < 2; k++) {
					v[k] = randDouble();
					// underflow
					double lim = sqrt(numeric_limits<double>::min() / (double) MAX(n, 2));
					if((v[k] > 0 && v[k] < lim) || (v[k] < 0 && v[k] > -lim)) v[k] = 1. / v[k];

					// overflow
					v[k] = fmod(v[k], sqrt(numeric_limits<double>::max() / (double) MAX(n, 2)));
				}

				A(i, j) = v[0];
				B(i, j) = v[1];
			}
		}

		// produit matriciel
		cout << "durée produit matriciel (en secondes) : " << endl;

		gettimeofday(&start, NULL);
		ColumnChecksumMatrix<double> Ac(A);
		RowChecksumMatrix<double> Br(B);
		gettimeofday(&end, NULL);
		t = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
		cout << "durée extension : " << t << endl;
		extensionFile << n << " " <<  t << endl;

		if(n <= 300) {
			/*cout << "Ac : " << Ac.toString() << endl;
			cout << "Br : " << Br.toString() << endl;
			cout << "C1f : " << C1f.toString() << endl;
			cout << "C1f.computeRowSum(1) : " << C1f.computeRowSum(1) << endl;
			cout << "C1f.computeRowSum(2) : " << C1f.computeRowSum(2) << endl;*/
			gettimeofday(&start, NULL);
			calculatorNaive.mult(C1f, Ac, Br);
			gettimeofday(&end, NULL);
			t = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
			cout << "	- Naïf : " << t << endl;
			naiveFile << n << " " <<  t << endl;
			/*cout << "Ac : " << Ac.toString() << endl;
			cout << "Br : " << Br.toString() << endl;
			cout << "C1f : " << C1f.toString() << endl;
			cout << "C1f.computeRowSum(1) : " << C1f.computeRowSum(1) << endl;
			cout << "C1f.computeRowSum(2) : " << C1f.computeRowSum(2) << endl;*/
			//CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
			for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= n + 1 ; j++) C1f(i, j) = 0;
		}

		gettimeofday(&start, NULL);
		calculatorAtlas.mult(C1f, Ac, Br);
		gettimeofday(&end, NULL);
		cout << "	- Atlas : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
		atlasFile << n << " " <<  dgemm << endl;
		calculChecksumsFile << n << " " <<  calculChecksums << endl;
		calculChecksumsMPackFile << n << " " <<  calculChecksumsMPack << endl;
		CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
		for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= n + 1 ; j++) C1f(i, j) = 0;

		gettimeofday(&start, NULL);
		calculatorGotoBlas.mult(C1f, Ac, Br);
		gettimeofday(&end, NULL);
		cout << "	- GotoBlas : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
		gotoBlasFile << n << " " <<  dgemm << endl;
		CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
		for(int i = 1; i <= n + 1; i++) for(int j = 1; j <= n + 1 ; j++) C1f(i, j) = 0;

		gettimeofday(&start, NULL);
		calculatorIntelMKL.mult(C1f, Ac, Br);
		gettimeofday(&end, NULL);
		cout << "	- IntelMKL : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
		intelMKLFile << n << " " <<  dgemm << endl;
		CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());

		if(n <= 2400) {
			gettimeofday(&start, NULL);
			calculatorMPack.mult(C1f, Ac, Br);
			gettimeofday(&end, NULL);
			cout << "	- Mpack : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
			mPackFile << n << " " <<  dgemm << endl;
			CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
		}

		CPPUNIT_ASSERT(!(C1f == C2f));
		(IMatrix<double>&) C2f = C1f;

		// correction 0 erreurs
		CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
		CPPUNIT_ASSERT(C1f == C2f);
		gettimeofday(&start, NULL);
		C1f.errorCorrection();
		gettimeofday(&end, NULL);
		cout << "durée correction 0 erreurs (en secondes) : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
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
		cout << "durée correction 1 erreurs (en secondes) : " << (end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0) << endl;
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
		t = end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 1000000.0;
		cout << "durée correction 2 erreurs (en secondes) : " << t << endl;
		correctionFile << n << " " <<  t << endl;
		CPPUNIT_ASSERT(!C1f.columnErrorDetection() && !C1f.rowErrorDetection());
		CPPUNIT_ASSERT(C1f == C2f);

	}
}
