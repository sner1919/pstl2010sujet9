#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include "../Types.hpp"

int main( int argc, char **argv) {
	/* ----------------------------------- */
    cout.precision(STREAM_PRECISION);
    mpf_set_default_prec(TYPE_SUM_PRECISION);
	/* ----------------------------------- */

	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(registry.makeTest());
	runner.run();
	return 0;
}
