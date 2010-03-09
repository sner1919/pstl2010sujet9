#include "MatrixTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( MatrixTest );

void MatrixTest::setUp() {}

void MatrixTest::tearDown() {}

void MatrixTest::testAll() {
    /* ---------- allocation statique de mémoire ---------- */
    double LData[2][2] = {{1., 0.}, {1.5, 1.}};
    double LBisData[2][2] = {{1., 0.}, {1.5, 1.}};
    double UData[2][2] = {{4., 3.}, {0., -1.5}};
    /* ---------------------------------------------------- */
    Matrix<double> L(LData[0], 2, 2);
    Matrix<double> LBis(LBisData[0], 2, 2);
    Matrix<double> U(UData[0], 2, 2);

	CPPUNIT_ASSERT(L.getM() == 2);
	CPPUNIT_ASSERT(L.getN() == 2);

	CPPUNIT_ASSERT(L.getData() == LData[0]);

	CPPUNIT_ASSERT(L(1,1) == 1.);
	CPPUNIT_ASSERT(L(1,2) == 0.);
	CPPUNIT_ASSERT(L(2,1) == 1.5);
	CPPUNIT_ASSERT(L(2,2) == 1.);

	CPPUNIT_ASSERT(L == L);
	CPPUNIT_ASSERT(L == LBis);
	CPPUNIT_ASSERT(!(L == U));

	cout << L.toString();
	CPPUNIT_ASSERT(L.toString().compare("[\n1 0 \n1.5 1 \n]\n") == 0);
}

