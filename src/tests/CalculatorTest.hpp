#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../Matrix.hpp"
#include "../interfaces/ICalculator.hpp"
#include "../AtlasAdapter.hpp"
#include "../GotoBlasAdapter.hpp"
#include "../IntelMKLAdapter.hpp"
#include "../MPackAdapter.hpp"
#include "../ErrorGenerator.hpp"
#include "../FullChecksumMatrix.hpp"
#include <vector>

class CalculatorTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(CalculatorTest);
		CPPUNIT_TEST(testMult);
		CPPUNIT_TEST(testSMult);
		CPPUNIT_TEST(testAdd);
		CPPUNIT_TEST(testTranspose);
		CPPUNIT_TEST(testLU);
		CPPUNIT_TEST_SUITE_END();

		Matrix<double> *L, *U, *A, *Ab;
		ColumnChecksumMatrix<double> *Lc;
		RowChecksumMatrix<double> *Ur;
		FullChecksumMatrix<double> *Af;
		ErrorGenerator<double> *g;
		AtlasAdapter *atlasAdapter;
		GotoBlasAdapter *gotoBlasAdapter;
		IntelMKLAdapter *intelMKLAdapter;
		MPackAdapter *mPackAdapter;
		vector< ICalculator<double>* > calc;

	public:
		void setUp();

		void tearDown();

		void testMult();

		void testSMult();

		void testAdd();

		void testTranspose();

		void testLU();
};