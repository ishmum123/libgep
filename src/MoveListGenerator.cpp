#include <iostream>
#include "MoveListGenerator.h"

void MoveListGenerator::generateOneArgFunction(int i) {
	OneArgFunction *f = ff.getOneArgFunction(rand() % numOneArgFunc);
	Move m {f, i};
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

void MoveListGenerator::generateMoveList() {
	for (int i = 0; i < (vd.size() - 1); i++) generateOneArgFunction(i);
	TwoArgFunction *f = ff.getTwoArgFunction(rand() % numTwoArgFunc);
	generateTwoRandomInts();
	Move m {f, x, y};
	vm.push_back(m);
	processTwoArgFunction(f);
}

vector<Move> MoveListGenerator::getMoveList() { 
	while (vd.size() > 1) generateMoveList(); 
	return vm;
}

MoveListGenerator::MoveListGenerator(int numVal, int j, int k) : numOneArgFunc (j), numTwoArgFunc (k) { 
	srand(time(0));
	for (int i = 0; i < numVal; i++) vd.push_back(1); 
}
