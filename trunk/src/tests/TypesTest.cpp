#include "TypesTest.hpp"
#include "../Types.hpp"
#include <cstdlib>
#include <limits>

CPPUNIT_TEST_SUITE_REGISTRATION(TypesTest);

void TypesTest::setUp() {}

void TypesTest::tearDown() {}

void TypesTest::testAll() {
	int n = 3;
	float af[7];
	double ad[7];

    int ind[3][2];
	ind[0][0] = numeric_limits<int>::min();
	ind[0][1] = 3;
	ind[1][0] = -2;
	ind[1][1] = 5;
	ind[2][0] = numeric_limits<int>::max() - 2;
	ind[2][1] = 3;

    for(int i = -n; i <= n; i++) {
		/* conversions */
		//cout << "++++++++++++++++++++++++" << endl;
		//cout << "float :" << endl;
		//cout << "i : " << i << endl;
    	float f = indexToFloat(i);
		//cout << "f = indexToFloat(i) : " << f << endl;
		//cout << "floatToIndex(f) : " << floatToIndex(f) << endl;
		CPPUNIT_ASSERT(floatToIndex(f) == i);
		CPPUNIT_ASSERT(indexToFloat(-i) == -f);
		//cout << "++++++++++++++++++++++++" << endl;

		for(int k = 0; k < 3; k++) {
			for(int j = ind[k][0], l = 0; l < ind[k][1]; j++, l++) {
				//cout << "++++++++++++++++++++++++" << endl;
				//cout << "double :" << endl;
				//cout << "i : " << i << endl;
				//cout << "j : " << j << endl;
				double d = indexToDouble(i, j);
				//cout << "d = indexToDouble(i, j) : " << d << endl;
				int a1, a0;
				doubleToIndex(d, &a1, &a0);
				//cout << "doubleToIndex(d, &a1, &a0)" << endl;
				//cout << "a1 : " << a1 << endl;
				//cout << "a0 : " << a0 << endl;
				CPPUNIT_ASSERT(a1 == i);
				CPPUNIT_ASSERT(a0 == j);
				CPPUNIT_ASSERT(indexToDouble(-i - 1, -j - 1) == -d);
			}
		}

		af[i + n] = f;
		ad[i + n] = indexToDouble(0, i);
	}


    for(int i = 0; i < 2 * n + 1; i++) {
    	for(int j = 0; j < 2 * n + 1; j++) {
        	for(int k = 0; k < 2 * n + 1; k++) {
        		CPPUNIT_ASSERT(equal(af[i], af[j], k) == (abs(i - j) <= k));
        		CPPUNIT_ASSERT(equal(ad[i], ad[j], 0, k) == (abs(i - j) <= k));
        	}
    	}
    }


    for(int i = 0; i <= 2 * n + 1; i++) {
        CPPUNIT_ASSERT(equal(indexToDouble(-1, numeric_limits<int>::max() - 1), indexToDouble(-1, numeric_limits<int>::max() - 1), 0, i) == (i >= 0));
        CPPUNIT_ASSERT(equal(indexToDouble(-1, numeric_limits<int>::max() - 1), indexToDouble(-1, numeric_limits<int>::max()), 0, i) == (i >= 1));
        CPPUNIT_ASSERT(equal(indexToDouble(-1, numeric_limits<int>::max() - 1), indexToDouble(0, numeric_limits<int>::min()), 0, i) == (i >= 2));
        CPPUNIT_ASSERT(equal(indexToDouble(-1, numeric_limits<int>::max() - 1), indexToDouble(0, numeric_limits<int>::min() + 1), 0, i) == (i >= 3));
        CPPUNIT_ASSERT(equal(indexToDouble(-1, numeric_limits<int>::max() - 1), indexToDouble(0, -3), 0, numeric_limits<int>::max() - i) == (i == 0));


        CPPUNIT_ASSERT(equal(indexToDouble(-1, numeric_limits<int>::max()), indexToDouble(-1, numeric_limits<int>::max() - 1), 0, i) == (i >= 1));
        CPPUNIT_ASSERT(equal(indexToDouble(-1, numeric_limits<int>::max()), indexToDouble(-1, numeric_limits<int>::max()), 0, i) == (i >= 0));
        CPPUNIT_ASSERT(equal(indexToDouble(-1, numeric_limits<int>::max()), indexToDouble(0, numeric_limits<int>::min()), 0, i) == (i >= 1));
        CPPUNIT_ASSERT(equal(indexToDouble(-1, numeric_limits<int>::max()), indexToDouble(0, numeric_limits<int>::min() + 1), 0, i) == (i >= 2));
        CPPUNIT_ASSERT(equal(indexToDouble(-1, numeric_limits<int>::max()), indexToDouble(0, -3), 0, numeric_limits<int>::max() - i) == (i <= 1));


        CPPUNIT_ASSERT(equal(indexToDouble(0, numeric_limits<int>::min()), indexToDouble(-1, numeric_limits<int>::max() - 1), 0, i) == (i >= 2));
        CPPUNIT_ASSERT(equal(indexToDouble(0, numeric_limits<int>::min()), indexToDouble(-1, numeric_limits<int>::max()), 0, i) == (i >= 1));
        CPPUNIT_ASSERT(equal(indexToDouble(0, numeric_limits<int>::min()), indexToDouble(0, numeric_limits<int>::min()), 0, i) == (i >= 0));;
        CPPUNIT_ASSERT(equal(indexToDouble(0, numeric_limits<int>::min()), indexToDouble(0, numeric_limits<int>::min() + 1), 0, i) == (i >= 1));
        CPPUNIT_ASSERT(equal(indexToDouble(0, numeric_limits<int>::min()), indexToDouble(0, -3), 0, numeric_limits<int>::max() - i) == (i <= 2));


        CPPUNIT_ASSERT(equal(indexToDouble(0, numeric_limits<int>::min() + 1), indexToDouble(-1, numeric_limits<int>::max() - 1), 0, i) == (i >= 3));
        CPPUNIT_ASSERT(equal(indexToDouble(0, numeric_limits<int>::min() + 1), indexToDouble(-1, numeric_limits<int>::max()), 0, i) == (i >= 2));
        CPPUNIT_ASSERT(equal(indexToDouble(0, numeric_limits<int>::min() + 1), indexToDouble(0, numeric_limits<int>::min()), 0, i) == (i >= 1));
        CPPUNIT_ASSERT(equal(indexToDouble(0, numeric_limits<int>::min() + 1), indexToDouble(0, numeric_limits<int>::min() + 1), 0, i) == (i >= 0));
        CPPUNIT_ASSERT(equal(indexToDouble(0, numeric_limits<int>::min() + 1), indexToDouble(0, -3), 0, numeric_limits<int>::max() - i) == (i <= 3));


        CPPUNIT_ASSERT(equal(indexToDouble(0, -3), indexToDouble(-1, numeric_limits<int>::max() - 1), 0, numeric_limits<int>::max() - i) == (i == 0));
        CPPUNIT_ASSERT(equal(indexToDouble(0, -3), indexToDouble(-1, numeric_limits<int>::max()), 0, numeric_limits<int>::max() - i) == (i <= 1));
        CPPUNIT_ASSERT(equal(indexToDouble(0, -3), indexToDouble(0, numeric_limits<int>::min()), 0, numeric_limits<int>::max() - i) == (i <= 2));
        CPPUNIT_ASSERT(equal(indexToDouble(0, -3), indexToDouble(0, numeric_limits<int>::min() + 1), 0, numeric_limits<int>::max() - i) == (i <= 3));
        CPPUNIT_ASSERT(equal(indexToDouble(0, -3), indexToDouble(0, -3), 0, i) == (i >= 0));
    }

}

