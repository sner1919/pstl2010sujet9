#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../Calculator.hpp"
#include "../CalculatorAtlas.hpp"
#include <vector>

class CalculatorTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(CalculatorTest);
		CPPUNIT_TEST(testMatrix);
		CPPUNIT_TEST(testRowColumn);
		CPPUNIT_TEST(testFull);
		CPPUNIT_TEST_SUITE_END();

		double *LData, *UData, *AData;
		Matrix<double> *L, *U, *A;
		vector<ICalculator<double>> calcs;

	public:
		void setUp();

		void tearDown();

		void testMatrix();

		void testRowColumn();

		void testFull();
};
