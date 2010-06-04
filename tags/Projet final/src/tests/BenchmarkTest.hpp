#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

class BenchmarkTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(BenchmarkTest);
		CPPUNIT_TEST(testPerf);
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();

		void tearDown();

		void testPerf();
};
