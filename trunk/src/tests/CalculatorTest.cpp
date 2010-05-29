#include "CalculatorTest.hpp"
#include "../Processor.hpp"
#include "../CalculatorNaive.hpp"
#include "../CalculatorBlasLapack.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(CalculatorTest);

void CalculatorTest::setUp() {
    L = new Matrix<double>(2, 2);
    (*L)(1, 1) = 1.; (*L)(1, 2) = 0.;
    (*L)(2, 1) = 1.5; (*L)(2, 2) = 1.;

    U = new Matrix<double>(2, 2);
    (*U)(1, 1) = 4.; (*U)(1, 2) = 3.;
    (*U)(2, 1) = 0.; (*U)(2, 2) = -1.5;

    A = new Matrix<double>(2, 2);
    (*A)(1, 1) = 4.; (*A)(1, 2) = 3.;
    (*A)(2, 1) = 6.; (*A)(2, 2) = 3.;

    Ab = new Matrix<double>(3, 3);
    (*Ab)(1, 1) = 4.; (*Ab)(1, 2) = 8.; (*Ab)(1, 3) = 7.;
    (*Ab)(2, 1) = -4.; (*Ab)(2, 2) = 1.; (*Ab)(2, 3) = 6.;
    (*Ab)(3, 1) = 8.; (*Ab)(3, 2) = 4.; (*Ab)(3, 3) = 3.;

    Lc = new ColumnChecksumMatrix<double>(*L);

    Ur = new RowChecksumMatrix<double>(*U);

    Af = new FullChecksumMatrix<double>(*A);

    g = new ErrorGenerator<double>;

    atlasAdapter = new AtlasAdapter;
    gotoBlasAdapter = new GotoBlasAdapter;
    intelMKLAdapter = new IntelMKLAdapter;

    calc.push_back(new CalculatorNaive<double>);
    calc.push_back(new Processor<double>(*calc[0], *g));
    calc.push_back(new CalculatorBlasLapack<double>(*atlasAdapter, 0));
    calc.push_back(new CalculatorBlasLapack<double>(*gotoBlasAdapter, 0));
    calc.push_back(new CalculatorBlasLapack<double>(*intelMKLAdapter, 0));
    calc.push_back(new CalculatorBlasLapack<double>(*atlasAdapter, 1));
    calc.push_back(new CalculatorBlasLapack<double>(*gotoBlasAdapter, 1));
    calc.push_back(new CalculatorBlasLapack<double>(*intelMKLAdapter, 1));
}

void CalculatorTest::tearDown() {
	delete L;
	delete U;
	delete A;
	delete Ab;
	delete Lc;
	delete Ur;
	delete Af;
	delete g;
	delete atlasAdapter;
	delete gotoBlasAdapter;
	delete intelMKLAdapter;
	delete dynamic_cast<CalculatorNaive<double>*>(calc[0]);
	delete dynamic_cast<Processor<double>*>(calc[1]);
	for(unsigned int i = 2; i < calc.size(); i++) delete dynamic_cast<CalculatorBlasLapack<double>*>(calc[i]);
}

void CalculatorTest::testMult() {
	Matrix<double> Aux1(2, 2);
    FullChecksumMatrix<double> Aux1f(Aux1);

	for(unsigned int k = 0; k < calc.size(); k++){
		CPPUNIT_ASSERT(!(Aux1 == *A));
		calc[k]->mult(Aux1, *L, *U);
		CPPUNIT_ASSERT(Aux1 == *A);
		for(int i = 1; i <= 2; i++) for(int j = 1; j <= 2 ; j++) Aux1(i, j) = 0;

		CPPUNIT_ASSERT(!(Aux1f == *Af));
		calc[k]->mult(Aux1f, *Lc, *Ur);
		CPPUNIT_ASSERT(Aux1f == *Af);
		for(int i = 1; i <= 3; i++) for(int j = 1; j <= 3 ; j++) Aux1f(i, j) = 0;
		cout << " >> " << endl;
	}
}

void CalculatorTest::testSMult() {
	Matrix<double> Aux1(2, 2);
    FullChecksumMatrix<double> Aux1f(Aux1);

	Matrix<double> Aux2(2, 2);
    Aux2(1, 1) = 8.; Aux2(1, 2) = 6.;
    Aux2(2, 1) = 12.; Aux2(2, 2) = 6.;
    FullChecksumMatrix<double> Aux2f(Aux2);

	for(unsigned int k = 0; k < calc.size(); k++){
		CPPUNIT_ASSERT(!(Aux1 == Aux2));
		calc[k]->mult(Aux1, *A, 2.);
		CPPUNIT_ASSERT(Aux1 == Aux2);
		for(int i = 1; i <= 2; i++) for(int j = 1; j <= 2 ; j++) Aux1(i, j) = 0;

		CPPUNIT_ASSERT(!(Aux1f == Aux2f));
		calc[k]->mult(Aux1f, *Af, 2.);
		CPPUNIT_ASSERT(Aux1f == Aux2f);
		for(int i = 1; i <= 3; i++) for(int j = 1; j <= 3 ; j++) Aux1f(i, j) = 0;
	}
}

void CalculatorTest::testAdd() {
	Matrix<double> Aux1(2, 2);
    FullChecksumMatrix<double> Aux1f(Aux1);

	Matrix<double> Aux2(2, 2);
    Aux2(1, 1) = 5.; Aux2(1, 2) = 3.;
    Aux2(2, 1) = 1.5; Aux2(2, 2) = -0.5;
    FullChecksumMatrix<double> Aux2f(Aux2);

	Matrix<double> Aux3(2, 2);
    Aux3(1, 1) = 9.; Aux3(1, 2) = 6.;
    Aux3(2, 1) = 7.5; Aux3(2, 2) = 2.5;
    FullChecksumMatrix<double> Aux3f(Aux3);

	for(unsigned int k = 0; k < calc.size(); k++){
		CPPUNIT_ASSERT(!(Aux1 == Aux2));
		calc[k]->add(Aux1, *L, *U);
		CPPUNIT_ASSERT(Aux1 == Aux2);
		for(int i = 1; i <= 2; i++) for(int j = 1; j <= 2 ; j++) Aux1(i, j) = 0;

		CPPUNIT_ASSERT(!(Aux1f == Aux3f));
		calc[k]->add(Aux1f, *Af, Aux2f);
		CPPUNIT_ASSERT(Aux1f == Aux3f);
		for(int i = 1; i <= 3; i++) for(int j = 1; j <= 3 ; j++) Aux1f(i, j) = 0;
	}
}

void CalculatorTest::testTranspose() {
	Matrix<double> Aux1(2, 2);
    FullChecksumMatrix<double> Aux1f(Aux1);

	Matrix<double> Aux2(2, 2);
    Aux2(1, 1) = 4.; Aux2(1, 2) = 0.;
    Aux2(2, 1) = 3.; Aux2(2, 2) = -1.5;
    FullChecksumMatrix<double> Aux2f(Aux2);

	for(unsigned int k = 0; k < calc.size(); k++){
		CPPUNIT_ASSERT(!(Aux1 == Aux2));
		calc[k]->transpose(Aux1, *U);
		CPPUNIT_ASSERT(Aux1 == Aux2);
		for(int i = 1; i <= 2; i++) for(int j = 1; j <= 2 ; j++) Aux1(i, j) = 0;
	}
}

void CalculatorTest::testLU() {
	Matrix<double> Aux1(2, 2);
	Matrix<double> Aux2(2, 2);
	Matrix<double> Aux3(2, 2);
	Matrix<double> Aux4(2, 2);

	Matrix<double> Aux1b(3, 3);
	Matrix<double> Aux2b(3, 3);
	Matrix<double> Aux3b(3, 3);
	Matrix<double> Aux4b(3, 3);

	for(unsigned int k = 0; k < calc.size(); k++){
		// A
		CPPUNIT_ASSERT(!(Aux1 == *A));
		calc[k]->LU(Aux1, Aux2, Aux3, *A);
		calc[k]->mult(Aux4, Aux1, Aux2);
		calc[k]->mult(Aux1, Aux4, Aux3);
		CPPUNIT_ASSERT(Aux1 == *A);
		for(int i = 1; i <= 2; i++) for(int j = 1; j <= 2 ; j++) {
			Aux1(i, j) = 0;
			Aux2(i, j) = 0;
			Aux3(i, j) = 0;
		}


		// l'algorithme naif et le processeur (car L ne serait pas une CCM et U une RCM) ne gèrent pas les permutations
		if(k > 1) {
			// Ab
			CPPUNIT_ASSERT(!(Aux1b == *Ab));
			calc[k]->LU(Aux1b, Aux2b, Aux3b, *Ab);
			calc[k]->mult(Aux4b, Aux1b, Aux2b);
			calc[k]->mult(Aux1b, Aux4b, Aux3b);
			CPPUNIT_ASSERT(Aux1b == *Ab);
			for(int i = 1; i <= 3; i++) for(int j = 1; j <= 3 ; j++) {
				Aux1b(i, j) = 0;
				Aux2b(i, j) = 0;
				Aux3b(i, j) = 0;
			}
		}
	}
}
