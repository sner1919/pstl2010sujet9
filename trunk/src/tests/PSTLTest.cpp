#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include "../Types.hpp"

int main( int argc, char **argv) {
	/* ----------------------------------- */
    cout.precision(50);
    mpf_set_default_prec(128);
	/* ----------------------------------- */

	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(registry.makeTest());
	runner.run();
	return 0;
}
