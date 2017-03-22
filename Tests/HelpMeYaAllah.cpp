#include "TestFunctions.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestFunctions);

using namespace CPPUNIT_NS;

class TestPerformer {
	TestResult tr;
	TestResultCollector trc;	
	void runTests();
public: 
	TestPerformer();
	bool getResult() { return trc.wasSuccessful(); }
};

void TestPerformer::runTests() {		
	TestRunner testrunner;
	testrunner.addTest (TestFactoryRegistry::getRegistry().makeTest());
	testrunner.run(tr);
	CompilerOutputter compileroutputter(&trc, cerr);
	compileroutputter.write ();
}

TestPerformer::TestPerformer() {
	tr.addListener (&trc);
	BriefTestProgressListener progress;
	tr.addListener (&progress);
	runTests();
}

int main(int argc, char* argv[]) {
	TestPerformer tp;
	return !tp.getResult();
}
