#include "MatrixTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( MatrixTest );

void MatrixTest::setUp() {
    /* ---------- allocation statique de mémoire ---------- */
    double LData[2][2] = {{1., 0.}, {1.5, 1.}};
    double UData[2][2] = {{4., 3.}, {0., -1.5}};
    /* ---------------------------------------------------- */
    L = new Matrix<double>(LData[0], 2, 2);
    Matrix<double> U(UData[0], 2, 2);
    Matrix<double> A(2, 2);

    cout << "L = " << L->toString() << endl;
    cout << "U = " << U.toString() << endl;

}

void MatrixTest::tearDown() {

}

void MatrixTest::testA() {
	CPPUNIT_ASSERT( 1 == 0);
}

