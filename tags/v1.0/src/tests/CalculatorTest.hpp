#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../Matrix.hpp"
#include "../CalculatorNaive.hpp"
#include "../CalculatorBlasLapack.hpp"
#include "../AtlasAdapter.hpp"
#include "../GotoBlasAdapter.hpp"
#include "../IntelMKLAdapter.hpp"
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

		IMatrix<PSTL_TYPE> *L, *U, *A, *Ab, *Aux1, *Aux2, *Aux3, *Aux4, *Aux1b, *Aux2b, *Aux3b, *Aux4b;
		IErrorGenerator<PSTL_TYPE> *g;
		IBlasLapackAdapter *atlasAdapter, *gotoBlasAdapter, *intelMKLAdapter;
		ICalculator<PSTL_TYPE> *calculatorNaive, *calculatorAtlas, *calculatorGotoBlas, *calculatorIntelMKL, *processor;
		vector< ICalculator<PSTL_TYPE>* > calc;

	public:
		void setUp();

		void tearDown();

		void testMult();

		void testSMult();

		void testAdd();

		void testTranspose();

		void testLU();
};
