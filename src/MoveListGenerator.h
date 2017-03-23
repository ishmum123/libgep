#ifndef __MOVE_GENERATOR_H__
#define __MOVE_GENERATOR_H__

#include <map>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "Function.h"

using namespace std;

//TODO: Very bad design here, Can probably be solved with factory pattern
//Memory Leakage largely due to this design
struct Move {
	Move(OneArgFunction *f, int i) : f1 (f), paramOne (i) {}
	Move(TwoArgFunction *f, int i, int j) : f2 (f), paramOne (i), paramTwo (j) {}
	OneArgFunction *f1;
	TwoArgFunction *f2;
	int paramOne;
	int paramTwo;
};

class MoveListGenerator {
	vector<double> vd;
	vector<Move> vm;
	FunctionFactory ff;
	int numOneArgFunc, numTwoArgFunc, x, y;
	void generateOneArgFunction(int i);
	void swapVal();
	void generateTwoRandomInts();
	void processTwoArgFunction(TwoArgFunction *f);
	void generateMoveList();
public:
	MoveListGenerator(int numVal, int j, int k);
	vector<Move> getMoveList();
};

#endif
