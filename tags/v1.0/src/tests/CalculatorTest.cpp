#include "CalculatorTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(CalculatorTest);

void CalculatorTest::setUp() {
    mpf_set_default_prec(128);

    L = new Matrix<PSTL_TYPE>(2, 2);
    (*L)(1, 1) = 1.; (*L)(1, 2) = 0.;
    (*L)(2, 1) = 1.5; (*L)(2, 2) = 1.;

    U = new Matrix<PSTL_TYPE>(2, 2);
    (*U)(1, 1) = 4.; (*U)(1, 2) = 3.;
    (*U)(2, 1) = 0.; (*U)(2, 2) = -1.5;

    A = new Matrix<PSTL_TYPE>(2, 2);
    (*A)(1, 1) = 4.; (*A)(1, 2) = 3.;
    (*A)(2, 1) = 6.; (*A)(2, 2) = 3.;

    Ab = new Matrix<PSTL_TYPE>(3, 3);
    (*Ab)(1, 1) = 4.; (*Ab)(1, 2) = 8.; (*Ab)(1, 3) = 7.;
    (*Ab)(2, 1) = -4.; (*Ab)(2, 2) = 1.; (*Ab)(2, 3) = 6.;
    (*Ab)(3, 1) = 8.; (*Ab)(3, 2) = 4.; (*Ab)(3, 3) = 3.;

    Aux1 = new Matrix<PSTL_TYPE>(2, 2);
    Aux2 = new Matrix<PSTL_TYPE>(2, 2);
    Aux3 = new Matrix<PSTL_TYPE>(2, 2);
    Aux4 = new Matrix<PSTL_TYPE>(2, 2);

    Aux1b = new Matrix<PSTL_TYPE>(3, 3);
    Aux2b = new Matrix<PSTL_TYPE>(3, 3);
    Aux3b = new Matrix<PSTL_TYPE>(3, 3);
    Aux4b = new Matrix<PSTL_TYPE>(3, 3);

    g = new ErrorGenerator<PSTL_TYPE>;

    atlasAdapter = new AtlasAdapter;
    gotoBlasAdapter = new GotoBlasAdapter;
    intelMKLAdapter = new IntelMKLAdapter;

    calculatorNaive = new CalculatorNaive<PSTL_TYPE>;
    calculatorAtlas = new CalculatorBlasLapack<PSTL_TYPE>(*atlasAdapter);
    calculatorGotoBlas = new CalculatorBlasLapack<PSTL_TYPE>(*gotoBlasAdapter);
    calculatorIntelMKL = new CalculatorBlasLapack<PSTL_TYPE>(*intelMKLAdapter);
    processor = new Processor<PSTL_TYPE>(*calculatorNaive, *g);

    calc.push_back(calculatorNaive);
    calc.push_back(calculatorAtlas);
    calc.push_back(calculatorGotoBlas);
    calc.push_back(calculatorIntelMKL);
    calc.push_back(processor);
}

void CalculatorTest::tearDown() {
	delete L;
	delete U;
	delete A;
	delete Ab;
	delete Aux1;
	delete Aux2;
	delete Aux3;
	delete Aux4;
	delete Aux1b;
	delete Aux2b;
	delete Aux3b;
	delete Aux4b;
	delete g;
	delete atlasAdapter;
	delete gotoBlasAdapter;
	delete intelMKLAdapter;
	delete calculatorNaive;
	delete calculatorAtlas;
	delete calculatorGotoBlas;
	delete calculatorIntelMKL;
	delete processor;
}

void CalculatorTest::testMult() {
	for(unsigned int i = 0; i < calc.size(); i++){
		CPPUNIT_ASSERT(!(*Aux1 == *A));
		calc[i]->mult(*Aux1, *L, *U);
		CPPUNIT_ASSERT(*Aux1 == *A);
		*Aux1 = *U;
	}
}

void CalculatorTest::testSMult() {
    (*Aux2)(1, 1) = 8.; (*Aux2)(1, 2) = 6.;
    (*Aux2)(2, 1) = 12; (*Aux2)(2, 2) = 6.;

	for(unsigned int i = 0; i < calc.size(); i++){
		CPPUNIT_ASSERT(!(*Aux1 == *Aux2));
		calc[i]->mult(*Aux1, *A, 2.);
		CPPUNIT_ASSERT(*Aux1 == *Aux2);
		*Aux1 = *U;
	}
}

void CalculatorTest::testAdd() {
    (*Aux2)(1, 1) = 5.; (*Aux2)(1, 2) = 3.;
    (*Aux2)(2, 1) = 1.5; (*Aux2)(2, 2) = -0.5;

	for(unsigned int i = 0; i < calc.size(); i++){
		CPPUNIT_ASSERT(!(*Aux1 == *Aux2));
		calc[i]->add(*Aux1, *L, *U);
		CPPUNIT_ASSERT(*Aux1 == *Aux2);
		*Aux1 = *U;
	}
}

void CalculatorTest::testTranspose() {
    (*Aux2)(1, 1) = 4.; (*Aux2)(1, 2) = 0.;
    (*Aux2)(2, 1) = 3; (*Aux2)(2, 2) = -1.5;

	for(unsigned int i = 0; i < calc.size(); i++){
		CPPUNIT_ASSERT(!(*Aux1 == *Aux2));
		calc[i]->transpose(*Aux1, *U);
		CPPUNIT_ASSERT(*Aux1 == *Aux2);
		*Aux1 = *U;
	}
}

void CalculatorTest::testLU() {
	for(unsigned int i = 0; i < calc.size(); i++){
		// A
		calc[i]->mult(*Aux4, *Aux1, *Aux2);
		calc[i]->mult(*Aux1, *Aux4, *Aux3);
		CPPUNIT_ASSERT(!(*Aux1 == *A));

		calc[i]->LU(*Aux1, *Aux2, *Aux3, *A);

		calc[i]->mult(*Aux4, *Aux1, *Aux2);
		calc[i]->mult(*Aux1, *Aux4, *Aux3);
		if(!(*Aux1 == *A)){
			cout << "Aux1 :" << Aux1->toString() << endl;
			cout << "A :" << A->toString() << endl;
		}
		CPPUNIT_ASSERT(*Aux1 == *A);
		*Aux1 = *A;
		*Aux2 = *A;
		*Aux3 = *A;


		// l'algorithme naif et le processeur (car L ne serait pas une CCM et U une RCM) ne gèrent pas les permutations
		if(i != 0 && i != calc.size() - 1) {
			// Ab
			calc[i]->mult(*Aux4b, *Aux1b, *Aux2b);
			calc[i]->mult(*Aux1b, *Aux4b, *Aux3b);
			CPPUNIT_ASSERT(!(*Aux1b == *Ab));

			calc[i]->LU(*Aux1b, *Aux2b, *Aux3b, *Ab);

			calc[i]->mult(*Aux4b, *Aux1b, *Aux2b);
			calc[i]->mult(*Aux1b, *Aux4b, *Aux3b);
			CPPUNIT_ASSERT(*Aux1b == *Ab);
			*Aux1b = *Ab;
			*Aux2b = *Ab;
			*Aux3b = *Ab;
		}
	}
}
