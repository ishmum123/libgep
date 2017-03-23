#include "MoveListGenerator.h"

using namespace std;

int main(int argc, char* argv[]) {
	FunctionFactory ff;
	TwoArgFunction *f = ff.getTwoArgFunction(4);
	f->initiate(5, 4);
	cout<<f->run()<<endl;
	delete f;
	return 0;
}
