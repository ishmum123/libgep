#include <iostream>
#include <string>
#include <list>
#include <math.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>

#include "../src/Function.h"

using namespace CppUnit;
using namespace std;

class TestFunctions : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(TestFunctions);
	CPPUNIT_TEST(testDoNothing);
	CPPUNIT_TEST(testInvertValue);
	CPPUNIT_TEST(testLog);
	CPPUNIT_TEST(testAdd);
	CPPUNIT_TEST(testSubtract);
	CPPUNIT_TEST(testMultiply);
	CPPUNIT_TEST(testDivide);
	CPPUNIT_TEST_SUITE_END();

	Function *f1, *f2, *f3, *f4, *f5, *f6, *f7;
	double x = 36.74, y = 55.50;

public:
	void setUp();
	void tearDown();

protected:
	void testDoNothing();
	void testInvertValue();
	void testLog();
	void testAdd();
	void testSubtract();
	void testMultiply();
	void testDivide();
};

void TestFunctions::setUp() {
	f1 = new DoNothingFunction(x);
	f2 = new InvertValueFunction(y);
	f3 = new LogFunction(x);
	f4 = new AddFunction(x, y);
	f5 = new SubtractFunction(x, y);
	f6 = new MultiplyFunction(x, y);
	f7 = new DivideFunction(x, y);
}

void TestFunctions::tearDown() { delete f1, f2, f3, f4, f5, f6, f7; }

void TestFunctions::testDoNothing() { CPPUNIT_ASSERT(x == f1->run()); }

void TestFunctions::testInvertValue() { CPPUNIT_ASSERT((-y) == f2->run()); }

void TestFunctions::testLog() { CPPUNIT_ASSERT(log(x) == f3->run()); }

void TestFunctions::testAdd() { CPPUNIT_ASSERT((x + y) == f4->run()); }

void TestFunctions::testSubtract() { CPPUNIT_ASSERT((x - y) == f5->run()); }

void TestFunctions::testMultiply() { CPPUNIT_ASSERT((x * y) == f6->run()); }

void TestFunctions::testDivide() { CPPUNIT_ASSERT((x / y) == f7->run()); }
