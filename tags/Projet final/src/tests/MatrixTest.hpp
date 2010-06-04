#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class MatrixTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(MatrixTest);
		CPPUNIT_TEST(testAll);
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();

		void tearDown();

		void testAll();
};
