#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "MoveListGenerator.h"
#include "MoveListImplementer.h"
#include "Function.h"
#include "FileProcessor.h"

using namespace std;

typedef vector<double> dv;
typedef vector<Move> mv;

//TODO: Remove un-deleted Pointers
int main(int argc, char* argv[]) {
	FileProcessor *fp = new FileProcessor("iris.data");
	FunctionFactory *ff = new FunctionFactory();
	MoveListGenerator *mlg = new MoveListGenerator(fp->getLineSize(), ff->getNumOfOneArgFunction(), ff->getNumOfTwoArgFunction());
	mv vm = mlg->getMoveList();
	map<int, dv> midv = fp->getLineValueMap();
	map<int, double> fvm;
	vector<double> vr;
	
	int c = 0;
	for (auto const &elem : midv) {
		MoveListImplementer *mli = new MoveListImplementer(midv[elem.first], vm);
		vr.push_back(mli->getResult());
		c++;
		delete mli;
	}


	double lVal = 0;
	for (double d : vr) lVal = ((d < lVal) && !isinf(d)) ? d : lVal;
	for (int i = 0; i < vr.size(); i++) vr.at(i) -= lVal;

	double hVal = 0;
	for (double d : vr) hVal = ((d > hVal) && !isinf(d)) ? d : hVal;
	for (int i = 0; i < vr.size(); i++) vr.at(i) /= hVal;

	for (int i = 0; i < vr.size(); i++) vr.at(i) = (vr.at(i) < 0.3333334) ? 0 : (vr.at(i) < 0.6666667) ? 1 : (vr.at(i) < 1) ? 2 : 3;

	int lc = 1;
	int ca = 0;
	for (double d : vr) ca += (d < fp->getClassNames().size()) ? (fp->getClassMap()[lc++] == fp->getClassNames().at(d)) : 0;

	if (!isinf(d)) cout<<"Percentage Correct: "<<(((double) ca / (lc- 1)) * 100)<<endl;

	delete fp, ff, mlg;
	return 0;
}
