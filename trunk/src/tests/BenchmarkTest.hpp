#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../FullChecksumMatrix.hpp"
#include "../Calculator.hpp"
#include "../ErrorGenerator.hpp"
#include <sys/time.h>

class BenchmarkTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(BenchmarkTest);
		CPPUNIT_TEST(testPerf);
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();

		void tearDown();

		void testPerf();
};
