#include "MatrixTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(MatrixTest);

void MatrixTest::setUp() {}

void MatrixTest::tearDown() {}

void MatrixTest::testAll() {
    PSTL_TYPE LData[2][2] = {{1., 0.}, {1.5, 1.}};
    PSTL_TYPE UData[2][2] = {{4., 3.}, {0., -1.5}};

    // constructeurs
    Matrix<PSTL_TYPE> L(LData[0], 2, 2);
    Matrix<PSTL_TYPE> U(UData[0], 2, 2);
    Matrix<PSTL_TYPE> LBis(2, 2);

    // getM(), getN()
	CPPUNIT_ASSERT(L.getM() == 2);
	CPPUNIT_ASSERT(L.getN() == 2);

	// getData()
	CPPUNIT_ASSERT(L.getData() == LData[0]);

	// operator()
	CPPUNIT_ASSERT(L(1,1) == 1.);
	CPPUNIT_ASSERT(L(1,2) == 0.);
	CPPUNIT_ASSERT(L(2,1) == 1.5);
	CPPUNIT_ASSERT(L(2,2) == 1.);

	LBis(1,1) = 1.;
	LBis(1,2) = 0.;
	LBis(2,1) = 1.5;
	LBis(2,2) = 1.;

	// operator==
	CPPUNIT_ASSERT(L == L);
	CPPUNIT_ASSERT(L == LBis);
	CPPUNIT_ASSERT(!(L == U));

	// toString()
	CPPUNIT_ASSERT(L.toString().compare("[\n1 0 \n1.5 1 \n]\n") == 0);

	// distance()
	CPPUNIT_ASSERT(L.distance(L) == 0);
	CPPUNIT_ASSERT(L.distance(LBis) == 0);
	CPPUNIT_ASSERT(L.distance(U) == 4);
	LBis(2,2) = 0.;
	CPPUNIT_ASSERT(L.distance(LBis) == 1);

	// weight()
	CPPUNIT_ASSERT(L.weight() == 3);
	CPPUNIT_ASSERT(LBis.weight() == 2);
	CPPUNIT_ASSERT(U.weight() == 3);
}

