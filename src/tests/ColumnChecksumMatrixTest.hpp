#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../ColumnChecksumMatrix.hpp"

class ColumnChecksumMatrixTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(ColumnChecksumMatrixTest);
		CPPUNIT_TEST(testMatrix);
		CPPUNIT_TEST(testRow);
		CPPUNIT_TEST_SUITE_END();

		double *UData;
		Matrix<double> *L, *L2, *U;
		ColumnChecksumMatrix<double> *Lc, *L2c, *Uc;

	public:
		void setUp();

		void tearDown();

		void testMatrix();

		void testRow();
};