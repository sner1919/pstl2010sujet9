#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../FullChecksumMatrix.hpp"
#include <ctime>
#include <cstdlib>

class FullChecksumMatrixTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(FullChecksumMatrixTest);
		CPPUNIT_TEST(testMatrix);
		CPPUNIT_TEST(testRowColumn);
		CPPUNIT_TEST(testFull);
		CPPUNIT_TEST_SUITE_END();

		double *LData, *UData, *LDataBis;
		Matrix<double> *L, *U, *LBis;
		FullChecksumMatrix<double> *Lf, *Uf, *LBisf;

	public:
		void setUp();

		void tearDown();

		void testMatrix();

		void testRowColumn();

		void testFull();

		void testPerf();
};
