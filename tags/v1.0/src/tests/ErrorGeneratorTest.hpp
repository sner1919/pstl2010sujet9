#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../ErrorGenerator.hpp"
#include "../Matrix.hpp"

class ErrorGeneratorTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(ErrorGeneratorTest);
		CPPUNIT_TEST(testAll);
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();

		void tearDown();

		void testAll();
};
