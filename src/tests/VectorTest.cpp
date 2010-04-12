#include "VectorTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(VectorTest);

void VectorTest::setUp() {}

void VectorTest::tearDown() {}

void VectorTest::testAll() {
    PSTL_TYPE UData[2] = {1.5, 1.};
    PSTL_TYPE VData[2] = {4., 3.};

    // constructeurs
    Vector<PSTL_TYPE> U(UData, 2);
    Vector<PSTL_TYPE> U2(2);
    Vector<PSTL_TYPE> V(VData, 2);

    // getM(), getN()
	CPPUNIT_ASSERT(U.getM() == 2);
	CPPUNIT_ASSERT(U.getN() == 1);

	// getData()
	CPPUNIT_ASSERT(U.getData() == UData);

	// getDataAllocation()
	CPPUNIT_ASSERT(!U.getDataAllocation());
	CPPUNIT_ASSERT(!V.getDataAllocation());
	CPPUNIT_ASSERT(U2.getDataAllocation());

	// operator==
	CPPUNIT_ASSERT(U == U);
	CPPUNIT_ASSERT(!(U == U2));
	CPPUNIT_ASSERT(!(U == V));

	// operator=
	(IMatrix<PSTL_TYPE>&) U2 = (IMatrix<PSTL_TYPE>&) V;
	CPPUNIT_ASSERT(U2 == V);
	CPPUNIT_ASSERT(!(U == U2));

	// operator()
	CPPUNIT_ASSERT(U(1) == 1.5);
	CPPUNIT_ASSERT(U(2) == 1.);
	U2(1) = 1.5;
	U2(2) = 1.;
	CPPUNIT_ASSERT(U2(1) == 1.5);
	CPPUNIT_ASSERT(U2(2) == 1.);
	CPPUNIT_ASSERT(U == U2);

	// distance()
	CPPUNIT_ASSERT(U.distance(U) == 0);
	CPPUNIT_ASSERT(U.distance(U2) == 0); CPPUNIT_ASSERT(U2.distance(U) == 0);
	CPPUNIT_ASSERT(U.distance(V) == 2); CPPUNIT_ASSERT(V.distance(U) == 2);
	U2(2) = 0.;
	CPPUNIT_ASSERT(U.distance(U2) == 1); CPPUNIT_ASSERT(U2.distance(U) == 1);

	// weight()
	CPPUNIT_ASSERT(U.weight() == 2);
	CPPUNIT_ASSERT(U2.weight() == 1);
	CPPUNIT_ASSERT(V.weight() == 2);

	// toString()
	CPPUNIT_ASSERT(U.toString().compare("[\n1.5 \n1 \n]\n") == 0);

	// locationId()
	for(int i = 1; i <= U.getM(); i++){
		for(int j = 1; j <= U.getN(); j++){
			for(int k = 1; k <= U.getM(); k++){
					for(int l = 1; l <= U.getN(); l++){
						if(!(i == k && j == l)) CPPUNIT_ASSERT(U.locationId(i, j) != U.locationId(k, l));
					}
			}
		}
	}

	// Contructeur par recopie
    Vector<PSTL_TYPE> U3(U2);
	CPPUNIT_ASSERT(U3.getDataAllocation());
	CPPUNIT_ASSERT(U3 == U2);
	U3(1) = 5.;
	CPPUNIT_ASSERT(U3(1) == 5. && U2(1) == 1.5);
	U3(1) = 1.5;
	CPPUNIT_ASSERT(U3 == U2);


    Vector<PSTL_TYPE> U4(V);
	CPPUNIT_ASSERT(!U4.getDataAllocation());
	CPPUNIT_ASSERT(U4 == V);
	U4(1) = 5.;
	CPPUNIT_ASSERT(U4 == V);
	CPPUNIT_ASSERT(U4(1) == 5. && V(1) == 5.);
	U4(1) = 1.;
	CPPUNIT_ASSERT(U4 == V);
}

