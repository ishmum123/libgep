#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>

#include "TestFunctions.h"
#include "TestFileProcessor.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestFunctions);
CPPUNIT_TEST_SUITE_REGISTRATION(TestFileProcessor);

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
