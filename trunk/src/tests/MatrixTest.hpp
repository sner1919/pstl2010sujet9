#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../Matrix.hpp"

class MatrixTest : public CppUnit::TestFixture {
CPPUNIT_TEST_SUITE( MatrixTest );
CPPUNIT_TEST( testA );
CPPUNIT_TEST_SUITE_END();

		IMatrix<double> *L, *U, *A;

	public:
		void setUp();

		void tearDown();

		void testA();
};
