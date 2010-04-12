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

    Aux1 = new Matrix<PSTL_TYPE>(2, 2);
    Aux2 = new Matrix<PSTL_TYPE>(2, 2);

    calc.push_back(new CalculatorNaive<PSTL_TYPE>);
    //calc.push_back(new CalculatorAtlas<PSTL_TYPE>);

    g = new ErrorGenerator<PSTL_TYPE>();
    calc.push_back(new Processor<PSTL_TYPE>(*calc[0], *g));
}

void CalculatorTest::tearDown() {
	delete L;
	delete U;
	delete A;
	delete Aux1;
	delete Aux2;
	delete g;
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
		CPPUNIT_ASSERT(!(*Aux1 == *L));
		CPPUNIT_ASSERT(!(*Aux2 == *U));
		calc[i]->LU(*Aux1, *Aux2, *A);
		CPPUNIT_ASSERT(*Aux1 == *L);
		CPPUNIT_ASSERT(*Aux2 == *U);
		*Aux1 = *U;
		*Aux2 = *L;
	}
}
