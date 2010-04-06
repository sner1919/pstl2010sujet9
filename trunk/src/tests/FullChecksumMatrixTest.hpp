#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../FullChecksumMatrix.hpp"

class FullChecksumMatrixTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(FullChecksumMatrixTest);
		CPPUNIT_TEST(testMatrix);
		CPPUNIT_TEST(testRowColumn);
		CPPUNIT_TEST(testFull);
		CPPUNIT_TEST_SUITE_END();

		PSTL_TYPE *LData;
		Matrix<PSTL_TYPE> *L, *U, *LBis;
		FullChecksumMatrix<PSTL_TYPE> *Lf, *Uf, *LBisf;

	public:
		void setUp();

		void tearDown();

		void testMatrix();

		void testRowColumn();

		void testFull();
};
