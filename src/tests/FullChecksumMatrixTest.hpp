#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../FullChecksumMatrix.hpp"

class FullChecksumMatrixTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(FullChecksumMatrixTest);
		CPPUNIT_TEST(testMatrix);
		CPPUNIT_TEST(testRowColumn);
		CPPUNIT_TEST(testFull);
		CPPUNIT_TEST_SUITE_END();

		PSTL_TYPE *UData;
		Matrix<PSTL_TYPE> *L, *L2, *U;
		FullChecksumMatrix<PSTL_TYPE> *Lf, *L2f, *Uf;

	public:
		void setUp();

		void tearDown();

		void testMatrix();

		void testRowColumn();

		void testFull();
};
