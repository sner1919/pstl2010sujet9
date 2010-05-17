#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../FullChecksumMatrix.hpp"

class FullChecksumMatrixTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(FullChecksumMatrixTest);
		CPPUNIT_TEST(testMatrix);
		CPPUNIT_TEST(testRowColumn);
		CPPUNIT_TEST(testFull);
		CPPUNIT_TEST_SUITE_END();

		double *UData;
		Matrix<double> *L, *L2, *U;
		FullChecksumMatrix<double> *Lf, *L2f, *Uf;

	public:
		void setUp();

		void tearDown();

		void testMatrix();

		void testRowColumn();

		void testFull();
};
