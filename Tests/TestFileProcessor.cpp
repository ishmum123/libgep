#include "../src/FileProcessor.h"	

int main(int argc, char* argv[]) {
	FileProcessor fp("../iris.data");
	for (string s : fp.getClassNames()) cout<<s<<endl;
	cout<<"Number of values per line: "<<fp.getLineSize()<<endl;
	return 0;
}
