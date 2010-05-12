#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include <sys/time.h>
#include <limits>
#include "../FullChecksumMatrix.hpp"
#include "../CalculatorNaive.hpp"
#include "../CalculatorBlasLapack.hpp"
#include "../AtlasAdapter.hpp"
#include "../GotoBlasAdapter.hpp"
#include "../IntelMKLAdapter.hpp"
#include "../ErrorGenerator.hpp"

class BenchmarkTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(BenchmarkTest);
		CPPUNIT_TEST(testPerf);
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();

		void tearDown();

		void testPerf();
};
