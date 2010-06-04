#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../RowChecksumMatrix.hpp"

class RowChecksumMatrixTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(RowChecksumMatrixTest);
		CPPUNIT_TEST(testMatrix);
		CPPUNIT_TEST(testRow);
		CPPUNIT_TEST_SUITE_END();

		double *UData;
		Matrix<double> *L, *L2, *U;
		RowChecksumMatrix<double> *Lr, *L2r, *Ur;

	public:
		void setUp();

		void tearDown();

		void testMatrix();

		void testRow();
};
