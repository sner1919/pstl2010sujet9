#include "FullChecksumMatrixTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(FullChecksumMatrixTest);

void FullChecksumMatrixTest::setUp() {
	LData = new PSTL_TYPE[4];
    LData[0] = 1.; LData[1] = 0.;
    LData[2] = 1.5; LData[3] = 1.;
    L = new Matrix<PSTL_TYPE>(LData, 2, 2);

    U = new Matrix<PSTL_TYPE>(2, 2);
    (*U)(1, 1) = 4.; (*U)(1, 2) = 3.;
    (*U)(2, 1) = 0.; (*U)(2, 2) = -1.5;


    PSTL_TYPE* LDataBis = new PSTL_TYPE[4];
    LDataBis[0] = 1.; LDataBis[1] = 0.;
    LDataBis[2] = 1.5; LDataBis[3] = 1.;
    LBis = new Matrix<PSTL_TYPE>(LDataBis, 2, 2);
    //LBis = new Matrix<PSTL_TYPE>(*L);

    CPPUNIT_ASSERT((*L)(1,1) == (*LBis)(1,1));

    Lf = new FullChecksumMatrix<PSTL_TYPE>(*L);
    Uf = new FullChecksumMatrix<PSTL_TYPE>(*U);
    LBisf = new FullChecksumMatrix<PSTL_TYPE>(*LBis);
}

void FullChecksumMatrixTest::tearDown() {
	delete [] L->getData();
	delete [] U->getData();
	delete [] LBis->getData();

	delete L;
	delete U;
	delete LBis;

	delete Lf;
	delete Uf;
	delete LBisf;
}

void FullChecksumMatrixTest::testMatrix() {
	IFullChecksumMatrix<PSTL_TYPE>& Lf = *this->Lf;
	IFullChecksumMatrix<PSTL_TYPE>& LBisf = *this->LBisf;
	IFullChecksumMatrix<PSTL_TYPE>& Uf = *this->Uf;

    // getM(), getN()
	CPPUNIT_ASSERT(Lf.getM() == 3);
	CPPUNIT_ASSERT(Lf.getN() == 3);

	// getData()
	CPPUNIT_ASSERT(Lf.getData() == LData);

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

	LBisf(1,1) = 1.;
	LBisf(1,2) = 0.;
	LBisf(1,3) = 1.;
	LBisf(2,1) = 1.5;
	LBisf(2,2) = 1.;
	LBisf(2,3) = 2.5;
	LBisf(3,1) = 2.5;
	LBisf(3,2) = 1.;
	LBisf(3,3) = 3.5;

	// operator==
	CPPUNIT_ASSERT(Lf == Lf);
	CPPUNIT_ASSERT(Lf == LBisf);
	CPPUNIT_ASSERT(!(Lf == Uf));

	// toString()
	CPPUNIT_ASSERT(Lf.toString().compare("[\n1 0 1 \n1.5 1 2.5 \n2.5 1 3.5 \n]\n") == 0);

	// distance()
	CPPUNIT_ASSERT(Lf.distance(Lf) == 0);
	CPPUNIT_ASSERT(Lf.distance(LBisf) == 0);
	CPPUNIT_ASSERT(Lf.distance(Uf) == 9);
	LBisf(2,2) = 0.;
	CPPUNIT_ASSERT(Lf.distance(LBisf) == 1);

	// weight()
	CPPUNIT_ASSERT(Lf.weight() == 8);
	CPPUNIT_ASSERT(LBisf.weight() == 7);
	CPPUNIT_ASSERT(Uf.weight() == 8);
}

void FullChecksumMatrixTest::testRowColumn() {
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
}

void FullChecksumMatrixTest::testFull() {
	srand(time(NULL));

	CPPUNIT_ASSERT(*Lf == *LBisf);

	// une erreur
	for(int i = 1; i <= Lf->getM(); i++){
		for(int j = 1; j <= Lf->getN(); j++){
			(*Lf)(i,j) = rand();
			CPPUNIT_ASSERT(!(*Lf == *LBisf));
			CPPUNIT_ASSERT(Lf->errorCorrection());
			CPPUNIT_ASSERT(*Lf == *LBisf);
		}
	}

	// deux erreurs même ligne (elles s'annulent)
	for(int i = 1; i <= Lf->getM(); i++){
		PSTL_TYPE x = rand();

		(*Lf)(i,1) += x;
		(*Lf)(i,2) -= x;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		(*Lf)(i,1) -= x;
		(*Lf)(i,2) += x;


		(*Lf)(i,1) += x;
		(*Lf)(i,3) += x;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		(*Lf)(i,1) -= x;
		(*Lf)(i,3) -= x;


		(*Lf)(i,2) += x;
		(*Lf)(i,3) += x;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		(*Lf)(i,2) -= x;
		(*Lf)(i,3) -= x;
	}

	// deux erreurs même colonne (elles s'annulent)
	for(int j = 1; j <= Lf->getN(); j++){
		PSTL_TYPE x = rand();

		(*Lf)(1,j) += x;
		(*Lf)(2,j) -= x;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		(*Lf)(1,j) -= x;
		(*Lf)(2,j) += x;


		(*Lf)(1,j) += x;
		(*Lf)(3,j) += x;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		(*Lf)(1,j) -= x;
		(*Lf)(3,j) -= x;


		(*Lf)(2,j) += x;
		(*Lf)(3,j) += x;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		(*Lf)(2,j) -= x;
		(*Lf)(3,j) -= x;
	}

	// deux erreurs même ligne (elles ne s'annulent pas)
	for(int i = 1; i <= Lf->getM(); i++){
		PSTL_TYPE x = rand();

		(*Lf)(i,1) += x;
		(*Lf)(i,2) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(Lf->errorCorrection());
		CPPUNIT_ASSERT(*Lf == *LBisf);

		(*Lf)(i,1) += x;
		(*Lf)(i,3) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(Lf->errorCorrection());
		CPPUNIT_ASSERT(*Lf == *LBisf);

		(*Lf)(i,2) += x;
		(*Lf)(i,3) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(Lf->errorCorrection());
		CPPUNIT_ASSERT(*Lf == *LBisf);
	}

	// deux erreurs même colonne (elles ne s'annulent pas)
	for(int j = 1; j <= Lf->getN(); j++){
		PSTL_TYPE x = rand();

		(*Lf)(1,j) += x;
		(*Lf)(2,j) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(Lf->errorCorrection());
		CPPUNIT_ASSERT(*Lf == *LBisf);

		(*Lf)(1,j) += x;
		(*Lf)(3,j) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(Lf->errorCorrection());
		CPPUNIT_ASSERT(*Lf == *LBisf);

		(*Lf)(2,j) += x;
		(*Lf)(3,j) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(Lf->errorCorrection());
		CPPUNIT_ASSERT(*Lf == *LBisf);
	}

	// deux erreurs non adjacentes
	for(int i = 1; i <= Lf->getM(); i++){
		PSTL_TYPE x = rand();
		int nextI = i % Lf->getM() + 1;
		(*Lf)(i,1) += x;
		(*Lf)(nextI,2) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *LBisf));

		(*Lf)(i,1) += x;
		(*Lf)(nextI,3) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *LBisf));

		(*Lf)(i,2) += x;
		(*Lf)(nextI,3) -= x + 1;
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
		CPPUNIT_ASSERT(!Lf->errorCorrection());
		CPPUNIT_ASSERT(!(*Lf == *LBisf));
	}
}
