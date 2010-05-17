#include "ColumnChecksumMatrixTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ColumnChecksumMatrixTest);

void ColumnChecksumMatrixTest::setUp() {
    L = new Matrix<double>(2, 2);
    (*L)(1, 1) = 1.; (*L)(1, 2) = 0.;
    (*L)(2, 1) = 1.5; (*L)(2, 2) = 1.;

    L2 = new Matrix<double>(*L);

	UData = new double[4];
    UData[0] = 4.; UData[1] = 3.;
    UData[2] = 0.; UData[3] = -1.5;
    U = new Matrix<double>(UData, 2, 2);

    Lc = new ColumnChecksumMatrix<double>(*L);
    L2c = new ColumnChecksumMatrix<double>(*L2);
    Uc = new ColumnChecksumMatrix<double>(*U);
}

void ColumnChecksumMatrixTest::tearDown() {
	delete [] U->getData();

	delete L;
	delete U;
	delete L2;

	delete Lc;
	delete Uc;
	delete L2c;
}

void ColumnChecksumMatrixTest::testMatrix() {
	ColumnChecksumMatrix<double>& Lc = *this->Lc;
	ColumnChecksumMatrix<double>& L2c = *this->L2c;
	ColumnChecksumMatrix<double>& Uc = *this->Uc;

    // getM(), getN()
	CPPUNIT_ASSERT(Lc.getM() == 3);
	CPPUNIT_ASSERT(Lc.getN() == 2);

	// getData()
	CPPUNIT_ASSERT(Uc.getData() == UData);

	// getDataAllocation()
	CPPUNIT_ASSERT(!Lc.getDataAllocation());
	CPPUNIT_ASSERT(!L2c.getDataAllocation());
	CPPUNIT_ASSERT(!Uc.getDataAllocation());

	// operator==
	CPPUNIT_ASSERT(Lc == Lc);
	CPPUNIT_ASSERT(Lc == L2c);
	CPPUNIT_ASSERT(!(Lc == Uc));

	// operator=
	(IMatrix<double>&) L2c = Uc;
	CPPUNIT_ASSERT(L2c == Uc);
	CPPUNIT_ASSERT(*L2 == *U);
	CPPUNIT_ASSERT(!(Lc == L2c));

	// operator()
	CPPUNIT_ASSERT(Lc(1,1) == 1.);
	CPPUNIT_ASSERT(Lc(1,2) == 0.);
	CPPUNIT_ASSERT(Lc(2,1) == 1.5);
	CPPUNIT_ASSERT(Lc(2,2) == 1.);
	CPPUNIT_ASSERT(Lc(3,1) == 2.5);
	CPPUNIT_ASSERT(Lc(3,2) == 1.);
	L2c(1,1) = 1.;
	L2c(1,2) = 0.;
	L2c(2,1) = 1.5;
	L2c(2,2) = 1.;
	L2c(3,1) = 2.5;
	L2c(3,2) = 1.;
	CPPUNIT_ASSERT(L2c(1,1) == 1.);
	CPPUNIT_ASSERT(L2c(1,2) == 0.);
	CPPUNIT_ASSERT(L2c(2,1) == 1.5);
	CPPUNIT_ASSERT(L2c(2,2) == 1.);
	CPPUNIT_ASSERT(L2c(3,1) == 2.5);
	CPPUNIT_ASSERT(L2c(3,2) == 1.);
	CPPUNIT_ASSERT(Lc == L2c);

	// distance()
	CPPUNIT_ASSERT(Lc.distance(Lc) == 0);
	CPPUNIT_ASSERT(Lc.distance(L2c) == 0); CPPUNIT_ASSERT(L2c.distance(Lc) == 0);
	CPPUNIT_ASSERT(Lc.distance(Uc) == 6); CPPUNIT_ASSERT(Uc.distance(Lc) == 6);
	L2c(2,2) = 0.;
	CPPUNIT_ASSERT(Lc.distance(L2c) == 1); CPPUNIT_ASSERT(L2c.distance(Lc) == 1);

	// weight()
	CPPUNIT_ASSERT(Lc.weight() == 5);
	CPPUNIT_ASSERT(L2c.weight() == 4);
	CPPUNIT_ASSERT(Uc.weight() == 5);

	// toString()
	CPPUNIT_ASSERT(Lc.toString().compare("[\n1 0 \n1.5 1 \n2.5 1 \n]\n") == 0);

	// locationId()
	for(int i = 1; i <= Lc.getM(); i++){
		for(int j = 1; j <= Lc.getN(); j++){
			for(int k = 1; k <= Lc.getM(); k++){
					for(int l = 1; l <= Lc.getN(); l++){
						if(!(i == k && j == l)) CPPUNIT_ASSERT(Lc.locationId(i, j) != Lc.locationId(k, l));
					}
			}
		}
	}
}

void ColumnChecksumMatrixTest::testRow() {
	// getColumnMatrix()
	CPPUNIT_ASSERT(&Lc->getColumnMatrix() == L);

	// getColumnSummationVector()
	CPPUNIT_ASSERT(Lc->getColumnSummationVector().toString().compare("[\n2.5 1 \n]\n") == 0);

	// computeColumnSum()
	CPPUNIT_ASSERT(Lc->computeColumnSum(1) == 0);
	CPPUNIT_ASSERT(Lc->computeColumnSum(2) == 0);
	(*Lc)(1, 2) -= 1;
	(*Lc)(3, 1) -= 3;
	CPPUNIT_ASSERT(Lc->computeColumnSum(1) == 3);
	CPPUNIT_ASSERT(Lc->computeColumnSum(2) == -1);
	(*Lc)(1, 2) += 1;
	(*Lc)(3, 1) += 3;

	// columnErrorDetection()
	CPPUNIT_ASSERT(!Lc->columnErrorDetection());
	(*Lc)(1, 2) -= 1;
	CPPUNIT_ASSERT(Lc->columnErrorDetection());
	(*Lc)(1, 2) += 1;
	CPPUNIT_ASSERT(!Lc->columnErrorDetection());
	(*Lc)(3, 1) -= 3;
	CPPUNIT_ASSERT(Lc->columnErrorDetection());
	(*Lc)(3, 1) += 3;
	CPPUNIT_ASSERT(!Lc->columnErrorDetection());
	(*Lc)(1, 2) -= 1;
	(*Lc)(3, 1) -= 3;
	CPPUNIT_ASSERT(Lc->columnErrorDetection());
	(*Lc)(1, 2) += 1;
	(*Lc)(3, 1) += 3;
	CPPUNIT_ASSERT(!Lc->columnErrorDetection());
}
