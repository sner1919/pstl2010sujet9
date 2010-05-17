#include "RowChecksumMatrixTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(RowChecksumMatrixTest);

void RowChecksumMatrixTest::setUp() {
    L = new Matrix<double>(2, 2);
    (*L)(1, 1) = 1.; (*L)(1, 2) = 0.;
    (*L)(2, 1) = 1.5; (*L)(2, 2) = 1.;

    L2 = new Matrix<double>(*L);

	UData = new double[4];
    UData[0] = 4.; UData[1] = 3.;
    UData[2] = 0.; UData[3] = -1.5;
    U = new Matrix<double>(UData, 2, 2);

    Lr = new RowChecksumMatrix<double>(*L);
    L2r = new RowChecksumMatrix<double>(*L2);
    Ur = new RowChecksumMatrix<double>(*U);
}

void RowChecksumMatrixTest::tearDown() {
	delete [] U->getData();

	delete L;
	delete U;
	delete L2;

	delete Lr;
	delete Ur;
	delete L2r;
}

void RowChecksumMatrixTest::testMatrix() {
	RowChecksumMatrix<double>& Lr = *this->Lr;
	RowChecksumMatrix<double>& L2r = *this->L2r;
	RowChecksumMatrix<double>& Ur = *this->Ur;

    // getM(), getN()
	CPPUNIT_ASSERT(Lr.getM() == 2);
	CPPUNIT_ASSERT(Lr.getN() == 3);

	// getData()
	CPPUNIT_ASSERT(Ur.getData() == UData);

	// getDataAllocation()
	CPPUNIT_ASSERT(!Lr.getDataAllocation());
	CPPUNIT_ASSERT(!L2r.getDataAllocation());
	CPPUNIT_ASSERT(!Ur.getDataAllocation());

	// operator==
	CPPUNIT_ASSERT(Lr == Lr);
	CPPUNIT_ASSERT(Lr == L2r);
	CPPUNIT_ASSERT(!(Lr == Ur));

	// operator=
	(IMatrix<double>&) L2r = Ur;
	CPPUNIT_ASSERT(L2r == Ur);
	CPPUNIT_ASSERT(*L2 == *U);
	CPPUNIT_ASSERT(!(Lr == L2r));

	// operator()
	CPPUNIT_ASSERT(Lr(1,1) == 1.);
	CPPUNIT_ASSERT(Lr(1,2) == 0.);
	CPPUNIT_ASSERT(Lr(1,3) == 1.);
	CPPUNIT_ASSERT(Lr(2,1) == 1.5);
	CPPUNIT_ASSERT(Lr(2,2) == 1.);
	CPPUNIT_ASSERT(Lr(2,3) == 2.5);
	L2r(1,1) = 1.;
	L2r(1,2) = 0.;
	L2r(1,3) = 1.;
	L2r(2,1) = 1.5;
	L2r(2,2) = 1.;
	L2r(2,3) = 2.5;
	CPPUNIT_ASSERT(L2r(1,1) == 1.);
	CPPUNIT_ASSERT(L2r(1,2) == 0.);
	CPPUNIT_ASSERT(L2r(1,3) == 1.);
	CPPUNIT_ASSERT(L2r(2,1) == 1.5);
	CPPUNIT_ASSERT(L2r(2,2) == 1.);
	CPPUNIT_ASSERT(L2r(2,3) == 2.5);
	CPPUNIT_ASSERT(Lr == L2r);

	// distance()
	CPPUNIT_ASSERT(Lr.distance(Lr) == 0);
	CPPUNIT_ASSERT(Lr.distance(L2r) == 0); CPPUNIT_ASSERT(L2r.distance(Lr) == 0);
	CPPUNIT_ASSERT(Lr.distance(Ur) == 6); CPPUNIT_ASSERT(Ur.distance(Lr) == 6);
	L2r(2,2) = 0.;
	CPPUNIT_ASSERT(Lr.distance(L2r) == 1); CPPUNIT_ASSERT(L2r.distance(Lr) == 1);

	// weight()
	CPPUNIT_ASSERT(Lr.weight() == 5);
	CPPUNIT_ASSERT(L2r.weight() == 4);
	CPPUNIT_ASSERT(Ur.weight() == 5);

	// toString()
	CPPUNIT_ASSERT(Lr.toString().compare("[\n1 0 1 \n1.5 1 2.5 \n]\n") == 0);

	// locationId()
	for(int i = 1; i <= Lr.getM(); i++){
		for(int j = 1; j <= Lr.getN(); j++){
			for(int k = 1; k <= Lr.getM(); k++){
					for(int l = 1; l <= Lr.getN(); l++){
						if(!(i == k && j == l)) CPPUNIT_ASSERT(Lr.locationId(i, j) != Lr.locationId(k, l));
					}
			}
		}
	}
}

void RowChecksumMatrixTest::testRow() {
	// getRowMatrix()
	CPPUNIT_ASSERT(&Lr->getRowMatrix() == L);

	// getRowSummationVector()
	CPPUNIT_ASSERT(Lr->getRowSummationVector().toString().compare("[\n1 \n2.5 \n]\n") == 0);

	// computeRowSum()
	CPPUNIT_ASSERT(Lr->computeRowSum(1) == 0);
	CPPUNIT_ASSERT(Lr->computeRowSum(2) == 0);
	(*Lr)(1, 2) -= 1;
	(*Lr)(2, 3) -= 2;
	CPPUNIT_ASSERT(Lr->computeRowSum(1) == -1);
	CPPUNIT_ASSERT(Lr->computeRowSum(2) == 2);
	(*Lr)(1, 2) += 1;
	(*Lr)(2, 3) += 2;

	// rowErrorDetection()
	CPPUNIT_ASSERT(!Lr->rowErrorDetection());
	(*Lr)(1, 2) -= 1;
	CPPUNIT_ASSERT(Lr->rowErrorDetection());
	(*Lr)(1, 2) += 1;
	CPPUNIT_ASSERT(!Lr->rowErrorDetection());
	(*Lr)(2, 3) -= 2;
	CPPUNIT_ASSERT(Lr->rowErrorDetection());
	(*Lr)(2, 3) += 2;
	CPPUNIT_ASSERT(!Lr->rowErrorDetection());
	(*Lr)(1, 2) -= 1;
	(*Lr)(2, 3) -= 2;
	CPPUNIT_ASSERT(Lr->rowErrorDetection());
	(*Lr)(1, 2) += 1;
	(*Lr)(2, 3) += 2;
	CPPUNIT_ASSERT(!Lr->rowErrorDetection());
}
