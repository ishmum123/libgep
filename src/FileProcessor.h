#ifndef __FILE_PROCESSOR_H__
#define __FILE_PROCESSOR_H__

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

using namespace std;

typedef vector<string> sv;
typedef vector<double> dv;
typedef map<int, dv> midv;
typedef map<int, string> mis;
typedef istringstream ss;
typedef ifstream fl;

class FileProcessor {
	string sline;
	sv classNames;
	mis classMap;
	midv lineValueMap;
	int lineSize = 0;
	int i = 0;
	void processLine();
	void processLineValues(sv line);
	void addValuesToMap(sv line);
	void addClassNameToMap(string name);
	bool classNameExists(string name);
public:
	FileProcessor(const string fileName);
	int getLineSize() { return lineSize; }
	sv getClassNames() { return classNames; }
	mis getClassMap() { return classMap; }
	midv getLineValueMap() { return lineValueMap; }
};

void FileProcessor::processLine() {
	string csv = "";
	ss s(sline);
	sv line;
	while (s) if (getline(s, csv, ',')) line.push_back(csv);
	if (!line.empty()) processLineValues(line);
}

void FileProcessor::addValuesToMap(sv line) {
	dv lineValues;
	for (string s : line) lineValues.push_back(atof(s.c_str()));
	lineValueMap[i] = lineValues;
}

bool FileProcessor::classNameExists(string name) {
	for (string s : classNames) if (s.compare(name) == 0) return true;
	return false;
}

void FileProcessor::addClassNameToMap(string name) {
	classMap[++i] = name;
	if (!classNameExists(name)) classNames.push_back(name);
}

void FileProcessor::processLineValues(sv line) {
	addClassNameToMap(line.at(line.size() - 1));
	line.pop_back();
	if (i == 1) lineSize = line.size();
	addValuesToMap(line);
}

FileProcessor::FileProcessor(const string fileName) {
	fl f(fileName);		
	while (f) if (getline(f, sline)) processLine();
}

#endif
