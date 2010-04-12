#include "FullChecksumMatrixTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(FullChecksumMatrixTest);

void FullChecksumMatrixTest::setUp() {
    L = new Matrix<PSTL_TYPE>(2, 2);
    (*L)(1, 1) = 1.; (*L)(1, 2) = 0.;
    (*L)(2, 1) = 1.5; (*L)(2, 2) = 1.;

    L2 = new Matrix<PSTL_TYPE>(*L);

	UData = new PSTL_TYPE[4];
    UData[0] = 4.; UData[1] = 3.;
    UData[2] = 0.; UData[3] = -1.5;
    U = new Matrix<PSTL_TYPE>(UData, 2, 2);

    Lf = new FullChecksumMatrix<PSTL_TYPE>(*L);
    L2f = new FullChecksumMatrix<PSTL_TYPE>(*L2);
    Uf = new FullChecksumMatrix<PSTL_TYPE>(*U);
}

void FullChecksumMatrixTest::tearDown() {
	delete [] U->getData();

	delete L;
	delete U;
	delete L2;

	delete Lf;
	delete Uf;
	delete L2f;
}

void FullChecksumMatrixTest::testMatrix() {
	FullChecksumMatrix<PSTL_TYPE>& Lf = *this->Lf;
	FullChecksumMatrix<PSTL_TYPE>& L2f = *this->L2f;
	FullChecksumMatrix<PSTL_TYPE>& Uf = *this->Uf;

    // getM(), getN()
	CPPUNIT_ASSERT(Lf.getM() == 3);
	CPPUNIT_ASSERT(Lf.getN() == 3);

	// getData()
	CPPUNIT_ASSERT(Uf.getData() == UData);

	// getDataAllocation()
	CPPUNIT_ASSERT(!Lf.getDataAllocation());
	CPPUNIT_ASSERT(!L2f.getDataAllocation());
	CPPUNIT_ASSERT(!Uf.getDataAllocation());

	// operator==
	CPPUNIT_ASSERT(Lf == Lf);
	CPPUNIT_ASSERT(Lf == L2f);
	CPPUNIT_ASSERT(!(Lf == Uf));

	// operator=
	(IMatrix<PSTL_TYPE>&) L2f = Uf;
	CPPUNIT_ASSERT(L2f == Uf);
	CPPUNIT_ASSERT(*L2 == *U);
	CPPUNIT_ASSERT(!(Lf == L2f));

	// operator()
	CPPUNIT_ASSERT(Lf(1,1) == 1.);
	CPPUNIT_ASSERT(Lf(1,2) == 0.);
	CPPUNIT_ASSERT(Lf(1,3) == 1.);
	CPPUNIT_ASSERT(Lf(2,1) == 1.5);
	CPPUNIT_ASSERT(Lf(2,2) == 1.);
	CPPUNIT_ASSERT(Lf(2,3) == 2.5);
	CPPUNIT_ASSERT(Lf(3,1) == 2.5);
	CPPUNIT_ASSERT(Lf(3,2) == 1.);
	CPPUNIT_ASSERT(Lf(3,3) == 3.5);
	L2f(1,1) = 1.;
	L2f(1,2) = 0.;
	L2f(1,3) = 1.;
	L2f(2,1) = 1.5;
	L2f(2,2) = 1.;
	L2f(2,3) = 2.5;
	L2f(3,1) = 2.5;
	L2f(3,2) = 1.;
	L2f(3,3) = 3.5;
	CPPUNIT_ASSERT(L2f(1,1) == 1.);
	CPPUNIT_ASSERT(L2f(1,2) == 0.);
	CPPUNIT_ASSERT(L2f(1,3) == 1.);
	CPPUNIT_ASSERT(L2f(2,1) == 1.5);
	CPPUNIT_ASSERT(L2f(2,2) == 1.);
	CPPUNIT_ASSERT(L2f(2,3) == 2.5);
	CPPUNIT_ASSERT(L2f(3,1) == 2.5);
	CPPUNIT_ASSERT(L2f(3,2) == 1.);
	CPPUNIT_ASSERT(L2f(3,3) == 3.5);
	CPPUNIT_ASSERT(Lf == L2f);

	// distance()
	CPPUNIT_ASSERT(Lf.distance(Lf) == 0);
	CPPUNIT_ASSERT(Lf.distance(L2f) == 0); CPPUNIT_ASSERT(L2f.distance(Lf) == 0);
	CPPUNIT_ASSERT(Lf.distance(Uf) == 9); CPPUNIT_ASSERT(Uf.distance(Lf) == 9);
	L2f(2,2) = 0.;
	CPPUNIT_ASSERT(Lf.distance(L2f) == 1); CPPUNIT_ASSERT(L2f.distance(Lf) == 1);

	// weight()
	CPPUNIT_ASSERT(Lf.weight() == 8);
	CPPUNIT_ASSERT(L2f.weight() == 7);
	CPPUNIT_ASSERT(Uf.weight() == 8);

	// toString()
	CPPUNIT_ASSERT(Lf.toString().compare("[\n1 0 1 \n1.5 1 2.5 \n2.5 1 3.5 \n]\n") == 0);

	// locationId()
	for(int i = 1; i <= Lf.getM(); i++){
		for(int j = 1; j <= Lf.getN(); j++){
			for(int k = 1; k <= Lf.getM(); k++){
					for(int l = 1; l <= Lf.getN(); l++){
						if(!(i == k && j == l)) CPPUNIT_ASSERT(Lf.locationId(i, j) != Lf.locationId(k, l));
					}
			}
		}
	}
}

void FullChecksumMatrixTest::testRowColumn() {
	// getRowMatrix(), getColumnMatrix()
	CPPUNIT_ASSERT(&Lf->getRowMatrix() == L);
	CPPUNIT_ASSERT(Lf->getColumnMatrix().toString().compare("[\n1 0 1 \n1.5 1 2.5 \n]\n") == 0);

	// getRowSummationVector(), getColumnSummationVector()
	CPPUNIT_ASSERT(Lf->getRowSummationVector().toString().compare("[\n1 \n2.5 \n]\n") == 0);
	CPPUNIT_ASSERT(Lf->getColumnSummationVector().toString().compare("[\n2.5 \n1 \n3.5 \n]\n") == 0);

	// computeRowSum(), computeColumnSum()
	CPPUNIT_ASSERT(Lf->computeRowSum(1) == 0);
	CPPUNIT_ASSERT(Lf->computeRowSum(2) == 0);
	CPPUNIT_ASSERT(Lf->computeRowSum(3) == 0);
	CPPUNIT_ASSERT(Lf->computeColumnSum(1) == 0);
	CPPUNIT_ASSERT(Lf->computeColumnSum(2) == 0);
	CPPUNIT_ASSERT(Lf->computeColumnSum(3) == 0);
	(*Lf)(1, 2) -= 1;
	(*Lf)(2, 3) -= 2;
	(*Lf)(3, 1) -= 3;
	CPPUNIT_ASSERT(Lf->computeRowSum(1) == -1);
	CPPUNIT_ASSERT(Lf->computeRowSum(2) == 2);
	CPPUNIT_ASSERT(Lf->computeRowSum(3) == -3);
	CPPUNIT_ASSERT(Lf->computeColumnSum(1) == 3);
	CPPUNIT_ASSERT(Lf->computeColumnSum(2) == -1);
	CPPUNIT_ASSERT(Lf->computeColumnSum(3) == -2);
	(*Lf)(1, 2) += 1;
	(*Lf)(2, 3) += 2;
	(*Lf)(3, 1) += 3;

	// rowErrorDetection(), columnErrorDetection()
	CPPUNIT_ASSERT(!Lf->rowErrorDetection());
	CPPUNIT_ASSERT(!Lf->columnErrorDetection());
	(*Lf)(1, 2) -= 1;
	CPPUNIT_ASSERT(Lf->rowErrorDetection());
	CPPUNIT_ASSERT(Lf->columnErrorDetection());
	(*Lf)(1, 2) += 1;
	CPPUNIT_ASSERT(!Lf->rowErrorDetection());
	CPPUNIT_ASSERT(!Lf->columnErrorDetection());
	(*Lf)(2, 3) -= 2;
	CPPUNIT_ASSERT(Lf->rowErrorDetection());
	CPPUNIT_ASSERT(Lf->columnErrorDetection());
	(*Lf)(2, 3) += 2;
	CPPUNIT_ASSERT(!Lf->rowErrorDetection());
	CPPUNIT_ASSERT(!Lf->columnErrorDetection());
	(*Lf)(3, 1) -= 3;
	CPPUNIT_ASSERT(Lf->rowErrorDetection());
	CPPUNIT_ASSERT(Lf->columnErrorDetection());
	(*Lf)(3, 1) += 3;
	CPPUNIT_ASSERT(!Lf->rowErrorDetection());
	CPPUNIT_ASSERT(!Lf->columnErrorDetection());
	(*Lf)(1, 2) -= 1;
	(*Lf)(2, 3) -= 2;
	CPPUNIT_ASSERT(Lf->rowErrorDetection());
	CPPUNIT_ASSERT(Lf->columnErrorDetection());
	(*Lf)(1, 2) += 1;
	(*Lf)(2, 3) += 2;
	CPPUNIT_ASSERT(!Lf->rowErrorDetection());
	CPPUNIT_ASSERT(!Lf->columnErrorDetection());
	(*Lf)(1, 2) -= 1;
	(*Lf)(3, 1) -= 3;
	CPPUNIT_ASSERT(Lf->rowErrorDetection());
	CPPUNIT_ASSERT(Lf->columnErrorDetection());
	(*Lf)(1, 2) += 1;
	(*Lf)(3, 1) += 3;
	CPPUNIT_ASSERT(!Lf->rowErrorDetection());
	CPPUNIT_ASSERT(!Lf->columnErrorDetection());
	(*Lf)(2, 3) -= 2;
	(*Lf)(3, 1) -= 3;
	CPPUNIT_ASSERT(Lf->rowErrorDetection());
	CPPUNIT_ASSERT(Lf->columnErrorDetection());
	(*Lf)(2, 3) += 2;
	(*Lf)(3, 1) += 3;
	CPPUNIT_ASSERT(!Lf->rowErrorDetection());
	CPPUNIT_ASSERT(!Lf->columnErrorDetection());
	(*Lf)(1, 2) -= 1;
	(*Lf)(2, 3) -= 2;
	(*Lf)(3, 1) -= 3;
	CPPUNIT_ASSERT(Lf->rowErrorDetection());
	CPPUNIT_ASSERT(Lf->columnErrorDetection());
	(*Lf)(1, 2) += 1;
	(*Lf)(2, 3) += 2;
	(*Lf)(3, 1) += 3;
	CPPUNIT_ASSERT(!Lf->rowErrorDetection());
	CPPUNIT_ASSERT(!Lf->columnErrorDetection());
}

void FullChecksumMatrixTest::testFull() {
	srand(time(NULL));

	CPPUNIT_ASSERT(*Lf == *L2f);

	// aucune erreur
	CPPUNIT_ASSERT(Lf->errorCorrection());
	CPPUNIT_ASSERT(*Lf == *L2f);

	// une erreur
	for(int i = 1; i <= Lf->getM(); i++){
		for(int j = 1; j <= Lf->getN(); j++){
			(*Lf)(i,j) = rand();
			CPPUNIT_ASSERT(!(*Lf == *L2f));
			CPPUNIT_ASSERT(Lf->errorCorrection());
			CPPUNIT_ASSERT(*Lf == *L2f);
		}
	}

	// deux erreurs même ligne (elles s'annulent)
	for(int i = 1; i <= Lf->getM(); i++){
		PSTL_TYPE x = rand();

		(*Lf)(i,1) += x;
		(*Lf)(i,2) -= x;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		(*Lf)(i,1) -= x;
		(*Lf)(i,2) += x;


		(*Lf)(i,1) += x;
		(*Lf)(i,3) += x;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		(*Lf)(i,1) -= x;
		(*Lf)(i,3) -= x;


		(*Lf)(i,2) += x;
		(*Lf)(i,3) += x;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		(*Lf)(i,2) -= x;
		(*Lf)(i,3) -= x;
	}

	// deux erreurs même colonne (elles s'annulent)
	for(int j = 1; j <= Lf->getN(); j++){
		PSTL_TYPE x = rand();

		(*Lf)(1,j) += x;
		(*Lf)(2,j) -= x;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		(*Lf)(1,j) -= x;
		(*Lf)(2,j) += x;


		(*Lf)(1,j) += x;
		(*Lf)(3,j) += x;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		(*Lf)(1,j) -= x;
		(*Lf)(3,j) -= x;


		(*Lf)(2,j) += x;
		(*Lf)(3,j) += x;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		(*Lf)(2,j) -= x;
		(*Lf)(3,j) -= x;
	}

	// deux erreurs même ligne (elles ne s'annulent pas)
	for(int i = 1; i <= Lf->getM(); i++){
		PSTL_TYPE x = rand();

		(*Lf)(i,1) += x;
		(*Lf)(i,2) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(Lf->errorCorrection());
		CPPUNIT_ASSERT(*Lf == *L2f);

		(*Lf)(i,1) += x;
		(*Lf)(i,3) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(Lf->errorCorrection());
		CPPUNIT_ASSERT(*Lf == *L2f);

		(*Lf)(i,2) += x;
		(*Lf)(i,3) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(Lf->errorCorrection());
		CPPUNIT_ASSERT(*Lf == *L2f);
	}

	// deux erreurs même colonne (elles ne s'annulent pas)
	for(int j = 1; j <= Lf->getN(); j++){
		PSTL_TYPE x = rand();

		(*Lf)(1,j) += x;
		(*Lf)(2,j) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(Lf->errorCorrection());
		CPPUNIT_ASSERT(*Lf == *L2f);

		(*Lf)(1,j) += x;
		(*Lf)(3,j) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(Lf->errorCorrection());
		CPPUNIT_ASSERT(*Lf == *L2f);

		(*Lf)(2,j) += x;
		(*Lf)(3,j) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(Lf->errorCorrection());
		CPPUNIT_ASSERT(*Lf == *L2f);
	}

	// deux erreurs non adjacentes
	for(int i = 1; i <= Lf->getM(); i++){
		PSTL_TYPE x = rand();
		int nextI = i % Lf->getM() + 1;
		(*Lf)(i,1) += x;
		(*Lf)(nextI,2) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *L2f));

		(*Lf)(i,1) += x;
		(*Lf)(nextI,3) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *L2f));

		(*Lf)(i,2) += x;
		(*Lf)(nextI,3) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *L2f));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *L2f));
	}
}
