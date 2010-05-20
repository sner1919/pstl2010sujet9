#include "MatrixTest.hpp"
#include "../Matrix.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(MatrixTest);

void MatrixTest::setUp() {}

void MatrixTest::tearDown() {}

void MatrixTest::testAll() {
    double LData[2][2] = {{1., 0.}, {1.5, 1.}};
    double UData[2][2] = {{4., 3.}, {0., -1.5}};

    // constructeurs
    Matrix<double> L(LData[0], 2, 2);
    Matrix<double> L2(2, 2);
    Matrix<double> U(UData[0], 2, 2);

    // getM(), getN()
	CPPUNIT_ASSERT(L.getM() == 2);
	CPPUNIT_ASSERT(L.getN() == 2);

	// getData()
	CPPUNIT_ASSERT(L.getData() == LData[0]);

	// getDataAllocation()
	CPPUNIT_ASSERT(!L.getDataAllocation());
	CPPUNIT_ASSERT(!U.getDataAllocation());
	CPPUNIT_ASSERT(L2.getDataAllocation());

	// operator==
	CPPUNIT_ASSERT(L == L);
	CPPUNIT_ASSERT(!(L == L2));
	CPPUNIT_ASSERT(!(L == U));

	// operator=
	L2 = (IMatrix<double>&) U;
	CPPUNIT_ASSERT(L2 == U);
	CPPUNIT_ASSERT(!(L == L2));

	// operator()
	CPPUNIT_ASSERT(L(1,1) == 1.);
	CPPUNIT_ASSERT(L(1,2) == 0.);
	CPPUNIT_ASSERT(L(2,1) == 1.5);
	CPPUNIT_ASSERT(L(2,2) == 1.);
	L2(1,1) = 1.;
	L2(1,2) = 0.;
	L2(2,1) = 1.5;
	L2(2,2) = 1.;
	CPPUNIT_ASSERT(L2(1,1) == 1.);
	CPPUNIT_ASSERT(L2(1,2) == 0.);
	CPPUNIT_ASSERT(L2(2,1) == 1.5);
	CPPUNIT_ASSERT(L2(2,2) == 1.);
	CPPUNIT_ASSERT(L == L2);

	// distance()
	CPPUNIT_ASSERT(L.distance(L) == 0);
	CPPUNIT_ASSERT(L.distance(L2) == 0); CPPUNIT_ASSERT(L2.distance(L) == 0);
	CPPUNIT_ASSERT(L.distance(U) == 4); CPPUNIT_ASSERT(U.distance(L) == 4);
	L2(2,2) = 0.;
	CPPUNIT_ASSERT(L.distance(L2) == 1); CPPUNIT_ASSERT(L2.distance(L) == 1);

	// weight()
	CPPUNIT_ASSERT(L.weight() == 3);
	CPPUNIT_ASSERT(L2.weight() == 2);
	CPPUNIT_ASSERT(U.weight() == 3);

	// toString()
	CPPUNIT_ASSERT(L.toString().compare("[\n1 0 \n1.5 1 \n]\n") == 0);

	// locationId()
	for(int i = 1; i <= L.getM(); i++){
		for(int j = 1; j <= L.getN(); j++){
			for(int k = 1; k <= L.getM(); k++){
					for(int l = 1; l <= L.getN(); l++){
						if(!(i == k && j == l)) CPPUNIT_ASSERT(L.locationId(i, j) != L.locationId(k, l));
					}
			}
		}
	}

	// Contructeur par recopie
    Matrix<double> L3(L2);
	CPPUNIT_ASSERT(L3.getDataAllocation());
	CPPUNIT_ASSERT(L3 == L2);
	L3(1,1) = 5.;
	CPPUNIT_ASSERT(L3(1,1) == 5. && L2(1,1) == 1.);
	L3(1,1) = 1.;
	CPPUNIT_ASSERT(L3 == L2);


    Matrix<double> L4(L);
	CPPUNIT_ASSERT(!L4.getDataAllocation());
	CPPUNIT_ASSERT(L4 == L);
	L4(1,1) = 5.;
	CPPUNIT_ASSERT(L4 == L);
	CPPUNIT_ASSERT(L4(1,1) == 5. && L(1,1) == 5.);
	L4(1,1) = 1.;
	CPPUNIT_ASSERT(L4 == L);

	// fromDouble(), toDouble()
    double t[2][2] = {{4., 3.}, {2., 1.}};
    L4.fromDouble(*t, true);
	CPPUNIT_ASSERT(L4(1,1) == 4.);
	CPPUNIT_ASSERT(L4(1,2) == 3.);
	CPPUNIT_ASSERT(L4(2,1) == 2.);
	CPPUNIT_ASSERT(L4(2,2) == 1.);
    L4.fromDouble(*t, false);
	CPPUNIT_ASSERT(L4(1,1) == 4.);
	CPPUNIT_ASSERT(L4(1,2) == 2.);
	CPPUNIT_ASSERT(L4(2,1) == 3.);
	CPPUNIT_ASSERT(L4(2,2) == 1.);

    double* t2 = new double[4];
    L4.toDouble(t2, true);
	CPPUNIT_ASSERT(t2[0] == 4.);
	CPPUNIT_ASSERT(t2[1] == 2.);
	CPPUNIT_ASSERT(t2[2] == 3.);
	CPPUNIT_ASSERT(t2[3] == 1.);
    L4.toDouble(t2, false);
	CPPUNIT_ASSERT(t2[0] == 4.);
	CPPUNIT_ASSERT(t2[1] == 3.);
	CPPUNIT_ASSERT(t2[2] == 2.);
	CPPUNIT_ASSERT(t2[3] == 1.);
	delete [] t2;
}

