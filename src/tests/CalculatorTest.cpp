#include "CalculatorTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(CalculatorTest);

void CalculatorTest::setUp() {
	PSTL_TYPE* LData = new PSTL_TYPE[4];
    LData[0] = 1.; LData[1] = 0.;
    LData[2] = 1.5; LData[3] = 1.;
    PSTL_TYPE* UData = new PSTL_TYPE[4];
    UData[0] = 4.; UData[1] = 3.;
    UData[2] = 0.; UData[3] = -1.5;
    PSTL_TYPE* AData = new PSTL_TYPE[4];
    AData[0] = 4.; AData[1] = 3.;
    AData[2] = 6.; AData[3] = 3.;

    L = new Matrix<PSTL_TYPE>(LData, 2, 2);
    U = new Matrix<PSTL_TYPE>(UData, 2, 2);
    A = new Matrix<PSTL_TYPE>(AData, 2, 2);

    calc.push_back(new CalculatorNaive<PSTL_TYPE>);
}

void CalculatorTest::tearDown() {
	delete [] L->getData();
	delete [] U->getData();
	delete [] A->getData();

	delete L;
	delete U;
	delete A;
}

void CalculatorTest::testMult() {
	Matrix<PSTL_TYPE> ABis(A->getM(), A->getN());

	/*for(unsigned int i = 0; i < calc.size(); i++){
		//calc[i].mult(ABis, *L, *U);
		//CPPUNIT_ASSERT(ABis == *A);
	}*/
}

void CalculatorTest::testSMult() {
}

void CalculatorTest::testAdd() {
}

void CalculatorTest::testTranspose() {
}

void CalculatorTest::testLU() {
}
