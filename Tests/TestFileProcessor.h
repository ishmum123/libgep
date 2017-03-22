#ifndef __TEST_FILE_PROCESSOR_H__
#define __TEST_FILE_PROCESSOR_H__

#include <string>
#include <vector>
#include <map>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <netinet/in.h>

#include "../src/FileProcessor.h"	

using namespace CppUnit;
using namespace std;

class TestFileProcessor : public TestFixture {

	CPPUNIT_TEST_SUITE(TestFileProcessor);
	CPPUNIT_TEST(testGetLineSize);
	CPPUNIT_TEST(testGetClassNames);
	CPPUNIT_TEST(testGetClassMap);
	CPPUNIT_TEST(testGetLineValueMap);
	CPPUNIT_TEST_SUITE_END();

	FileProcessor *fp;
	string s1 = "Iris-setosa", s2 = "Iris-versicolor", s3 = "Iris-virginica";
public: 
	void setUp() { fp = new FileProcessor("iris.data"); }
	void tearDown() { delete fp; }
protected: 
	void testGetLineSize() { CPPUNIT_ASSERT(4 == fp->getLineSize()); }
	void testGetClassNames();
	void testGetClassMap();
	void testGetLineValueMap();
};

void TestFileProcessor::testGetLineValueMap() {
	vector<double> dv1 = fp->getLineValueMap()[150];
	//CPPUNIT_ASSERT(1.8 = dv1.at(3));
	//TODO: This as well
}

void TestFileProcessor::testGetClassMap() {
	map<int, string> m = fp->getClassMap();
	//TODO: This is terribly wrong. would need to get back to it
	CPPUNIT_ASSERT(s1 == m[1]);
	CPPUNIT_ASSERT(s3 == m[2]);
}

void TestFileProcessor::testGetClassNames() {
	vector<string> vs = {s1, s2, s3};
	CPPUNIT_ASSERT(vs == fp->getClassNames());
}

#endif
