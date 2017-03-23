#include <iostream>
#include <vector>
#include "MoveListGenerator.h"

using namespace std;

typedef vector<double> dv;
typedef vector<Move> mv;

class MoveListImplementer {
	dv vd;
	double result;
	mv vm;
	int j = 0;
	void implementMoves();
	void implementOneArgMove(int i);
public:	
	MoveListImplementer(dv v1, mv v2);
	double getResult() { return result; }
};

MoveListImplementer::MoveListImplementer(dv v1, mv v2) : vd (v1), vm (v2) {
	//TODO: Major Memory Leakage Issue
	while (vd.size() > 1) implementMoves();
	result = vd.at(0);
}

void MoveListImplementer::implementMoves() {
	for (int i = 0; i < (vd.size() - 1); i++) implementOneArgMove(i);
	TwoArgFunction *f = vm.at(j).f2;
	f->initiate(vd.at(vm.at(j).paramOne), vd.at(vm.at(j).paramTwo));
	vd.push_back(f->run());
	vd.erase(vd.begin() + vm.at(j).paramTwo);
	vd.erase(vd.begin() + vm.at(j++).paramOne);
}	

void MoveListImplementer::implementOneArgMove(int i) {
	OneArgFunction *f = vm.at(j++).f1;
	f->initiate(vd.at(i));
	vd.at(i) = f->run();
}
