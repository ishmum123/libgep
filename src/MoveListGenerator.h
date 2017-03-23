#ifndef __MOVE_GENERATOR_H__
#define __MOVE_GENERATOR_H__

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Function.h"
#include <time.h>

using namespace std;

struct Move {
	Move(Function *f) : f (f) {}
	Function *f;
};

struct TwoArgMove : public Move {
	TwoArgMove(Function *f, int i, int j) : Move(f), paramOne (i), paramTwo (j) {}
	int paramOne;
	int paramTwo;
};

struct OneArgMove : public Move {
	OneArgMove(Function *f, int i) : Move(f), paramOne (i) {}
	int paramOne;
};

class MoveListGenerator {
	vector<double> vd;
	vector<Move> vm;
	FunctionFactory ff;
	int numOneArgFunc, numTwoArgFunc, x, y;
	void generateOneArgFunction(int i);
	void swapVal();
	void generateTwoRandomInts();
	void generateTwoArgFunction();
	void processTwoArgFunction(TwoArgFunction *f);
	void generateMoveList();
public:
	MoveListGenerator(int numVal, int j, int k);
	vector<double> getDoubleVector() { return vd; }
};

void MoveListGenerator::generateOneArgFunction(int i) {
	OneArgFunction *f = ff.getOneArgFunction(rand() % numOneArgFunc);
	OneArgMove m {f, i};
	vm.push_back(m);
	f->initiate(vd.at(i));
	vd.at(i) = f->run();
}

void MoveListGenerator::swapVal() {
	int tmp = x;
	x = y;
	y = tmp;
}

void MoveListGenerator::generateTwoRandomInts() {
	x = (rand() % vd.size());
	y = (rand() % vd.size());
	while (x == y) y = (rand() % vd.size());
	if (y < x) swapVal();
}

void MoveListGenerator::processTwoArgFunction(TwoArgFunction *f) {
	f->initiate(vd.at(x), vd.at(y));
	vd.push_back(f->run());
	vd.erase(vd.begin() + y);
	vd.erase(vd.begin() + x);
}

void MoveListGenerator::generateTwoArgFunction() {
	TwoArgFunction *f = ff.getTwoArgFunction(rand() % numTwoArgFunc);
	TwoArgMove m {f, x, y};
	vm.push_back(m);
	processTwoArgFunction(f);
}

void MoveListGenerator::generateMoveList() {
	for (int i = 0; i < (vd.size() - 1); i++) generateOneArgFunction(i);
	if (vd.size() > 1) generateTwoArgFunction();
}

MoveListGenerator::MoveListGenerator(int numVal, int j, int k) : numOneArgFunc (j), numTwoArgFunc (k) { 
	srand(time(0));
	for (int i = 0; i < numVal; i++) vd.push_back(1); 
	while (vd.size() > 1) generateMoveList();
}

#endif
