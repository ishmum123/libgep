#ifndef __MOVE_GENERATOR_H__
#define __MOVE_GENERATOR_H__

#include <vector>
#include "Function.h"

using namespace std;

struct Move {
	unsigned short funcNum;
};

struct TwoArgMove : public Move {
	int paramOne;
	int paramTwo;
};

struct OneArgMove : public Move {
	int paramOne;
};

class MoveListGenerator {
	vector<double> vd;
	vector<Move> vm;
	int numOneArgFunc, numTwoArgFunc, x, y;
	void swapVal(int *x, int *y);
	void applyMovesToVector();
public:
	MoveListGenerator(int i);
};

void MoveListGenerator::applyTwoArgMove() {
	TwoArgMove m = {(rand() % k), vd.at(x), vd.at(y)};
	vd.push_back(ff.getResult(m.funcNum, vd.at(m.paramOne), vd.at(m.paramTwo)));
	vd.erase(vd.begin() + x);
	vd.erase(vd.begin() + (y - 1))
	vm.push_back(m);
}

void MoveListGenerator::getTwoRandomNumbers() {
	x = (rand() % (vd.size() - 1));
	y = (rand() % (vd.size() - 1));
	while (x == y) y = (rand() % (vd.size() - 1));
	if (y > x) swapVal(&x, &y);
}

void MoveListGenerator::applyOneArgMove(int i, int j) {
	OneArgMove m {(rand() % j), i};
	vd.at(i) = ff.getResult(m.funcNum, vd.at(i));
	vm.push_back(m);
}

void MoveListGenerator::applyMovesToVector() {
	for (int i = 0; i < vd.size(); i++) applyOneArgMove(i, j);
	getTwoRandomNumbers();
	applyTwoArgMove();
}

void MoveListGenerator::swapVal(int *x, int *y) {
	int tmp = x;
	x = y;
	y = tmp;
}

MoveListGenerator(int numVal, int j, int k) : numOneArgFunc (j), numTwoArgFunc (k) { 
	srand(time(0));
	for (int i = 0; i < numVal; i++) vd.push_back(1); 
	FunctionFactory ff;
	while (vd.size() > 1) applyMovesToVector();
}

#endif
