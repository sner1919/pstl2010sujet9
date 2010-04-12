#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../Vector.hpp"

class VectorTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(VectorTest);
		CPPUNIT_TEST(testAll);
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();

		void tearDown();

		void testAll();
};
