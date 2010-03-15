#include "FullChecksumMatrixTest.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(FullChecksumMatrixTest);

void FullChecksumMatrixTest::setUp() {
	LData = new double[4];
    LData[0] = 1.; LData[1] = 0.;
    LData[2] = 1.5; LData[3] = 1.;
    LDataBis = new double[4];
    LDataBis[0] = 1.; LDataBis[1] = 0.;
    LDataBis[2] = 1.5; LDataBis[3] = 1.;
    UData = new double[4];
    UData[0] = 4.; UData[1] = 3.;
    UData[2] = 0.; UData[3] = -1.5;

    L = new Matrix<double>(LData, 2, 2);
    U = new Matrix<double>(UData, 2, 2);
    LBis = new Matrix<double>(LDataBis, 2, 2);

    Lf = new FullChecksumMatrix<double>(*L);
    Uf = new FullChecksumMatrix<double>(*U);
    LBisf = new FullChecksumMatrix<double>(*LBis);
}

void FullChecksumMatrixTest::tearDown() {
	delete [] LData;
	delete [] UData;
	delete [] LDataBis;

	delete L;
	delete U;
	delete LBis;

	delete Lf;
	delete Uf;
	delete LBisf;
}

void FullChecksumMatrixTest::testMatrix() {
	IFullChecksumMatrix<double>& Lf = *this->Lf;
	IFullChecksumMatrix<double>& LBisf = *this->LBisf;
	IFullChecksumMatrix<double>& Uf = *this->Uf;

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
		double x = rand();

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
		double x = rand();

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
		double x = rand();

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
		double x = rand();

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
		double x = rand();
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

void FullChecksumMatrixTest::testPerf() {/*
	clock_t endwait;
	clock_t endwait;
	srand(time(NULL));

	Matrix<double> M(3000, 3000);
	cout << "temps "(temps_final - temps_initial) / CLOCKS_PER_SEC * 1000;*/

}
