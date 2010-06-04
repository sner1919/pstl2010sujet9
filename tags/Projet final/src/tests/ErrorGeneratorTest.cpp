#include "ErrorGeneratorTest.hpp"
#include "../ErrorGenerator.hpp"
#include "../Matrix.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(ErrorGeneratorTest);

void ErrorGeneratorTest::setUp() {}

void ErrorGeneratorTest::tearDown() {}

void ErrorGeneratorTest::testAll() {
	ErrorGenerator<double> g;
	int nbEmplacements;

    Matrix<double> L(2, 2);
    L(1, 1) = 1.; L(1, 2) = 0.;
    L(2, 1) = 1.5; L(2, 2) = 1.;

    Matrix<double> L2(L);

    // generateError()
    for(int iMin = 1; iMin <= 2; iMin++) {
		for(int jMin = 1; jMin <= 2; jMin++) {
		    for(int iMax = iMin; iMax <= 2; iMax++) {
				for(int jMax = jMin; jMax <= 2; jMax++) {
					if(iMin == iMax || jMin == jMax) {
						// 2 emplacements au plus
						if(iMin == iMax && jMin == jMax) nbEmplacements = 1;
						else nbEmplacements = 2;
					} else {
						nbEmplacements = 4;
					}

					// Vérifications
					for(int nb = 1; nb <= nbEmplacements; nb++) {
						CPPUNIT_ASSERT(L.distance(L2) == 0);
						pthread_t th = g.generateError(L, nb, iMin, iMax, jMin, jMax);
						pthread_join(th, NULL);
						CPPUNIT_ASSERT(L.distance(L2) == nb);

						int distance = 0;
						for(int i = iMin; i <= iMax; i++){
							for(int j = jMin; j <= jMax; j++){
								if(L(i, j) != L2(i, j)) distance++;
							}
						}
						CPPUNIT_ASSERT(distance == nb);
						L = (IMatrix<double>&) L2;
					}
				}
		    }
		}
	}

    // generateCorrectableError()
}
