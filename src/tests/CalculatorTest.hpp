#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../Matrix.hpp"
#include "../CalculatorNaive.hpp"
#include "../CalculatorAtlas.hpp"
#include "../Processor.hpp"
#include "../ErrorGenerator.hpp"
#include <vector>

class CalculatorTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(CalculatorTest);
		CPPUNIT_TEST(testMult);
		CPPUNIT_TEST(testSMult);
		CPPUNIT_TEST(testAdd);
		CPPUNIT_TEST(testTranspose);
		CPPUNIT_TEST(testLU);
		CPPUNIT_TEST_SUITE_END();

		IMatrix<PSTL_TYPE> *L, *U, *A, *Aux1, *Aux2;
		vector< ICalculator<PSTL_TYPE>* > calc;
		IErrorGenerator<PSTL_TYPE> *g;

	public:
		void setUp();

		void tearDown();

		void testMult();

		void testSMult();

		void testAdd();

		void testTranspose();

		void testLU();
};