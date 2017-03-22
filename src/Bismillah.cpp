#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <map>
#include "Function.h"
#include "MoveGenerator.h"

using namespace std;

typedef vector<Function*> vfp;
typedef vector<double> dv;
typedef vector<string> sv;
typedef vector<Move> vmv;

struct S { unsigned int b : 2; };

typedef vector<S> vsb;

vfp getFunctions() { return {new AddFunction(), new SubtractFunction(), new MultiplyFunction(), new DivideFunction()}; }

int getRandNum(int i) { return (rand() % i); }

void swapVal(int &i, int &j) {
    int k = i;
    i = j;
    j = k;
}

vector<int> getRandSels(int i) {
    int sel1 = getRandNum(i);
    int sel2 = getRandNum(i);
    while (sel1 == sel2) sel2 = getRandNum(i);
    if (sel2 < sel1) swapVal(sel1, sel2);
    return {sel1, sel2};
}

dv execute(Move m, dv vd, vfp vf) {
    double d = vf.at(m.funcNum)->run(vd.at(m.paramOne), vd.at(m.paramTwo));
    vd.erase(vd.begin() + m.paramOne);
    vd.erase(vd.begin() + (m.paramTwo - 1));
    vd.push_back(d);
    return vd;
}

int makeMoveOnVector(int vs, dv &vd, vmv &mv, vfp vf) { 
    vector<int> vi = getRandSels(vs);
    Move m {getRandNum(vf.size()), vi[0], vi[1]};
    mv.push_back(m);
    vd = execute(m, vd, vf);
    return vd.size();
}

vmv getClassifyDataMove(dv vd) {
    vfp vf = getFunctions();
    int vs = vd.size();
    vmv mv;
    while (vs > 1) vs = makeMoveOnVector(vs, vd, mv, vf);
    cout<<"Calculated value = "<<vd.at(0)<<endl;
    for (Function *f : vf) delete f;
    return mv;
}

void processSeparatedValues(sv line, vmv moveList, vfp fv, dv *valueList) {
    dv vd;
    for (int i = 0; i < (line.size() - 2); i++) vd.push_back(atof(line.at(i).c_str()));
    for (Move m : moveList) vd = execute(m, vd, fv);
    valueList->push_back(vd.at(0));
}

void processLine(string sline, vmv moveList, vfp fv, dv *valueList) {
    string csv = "";
    sv line;
    istringstream s(sline);
    while (s) if (getline(s, csv, ',')) line.push_back(csv);
    if (!line.empty()) processSeparatedValues(line, moveList, fv, valueList);
}

void shiftNegative(dv *valueList) {
    double lowVal = 0;
    for (double d : *valueList) lowVal = (d < lowVal) ? d : lowVal;
    if (lowVal != 0) for (int i = 0; i < valueList->size(); i++) valueList->at(i) += lowVal;
}

void shrinkPositive(dv *valueList) {
    double highVal = 0;
    for (double d : *valueList) highVal = (d > highVal) ? d : highVal;
    if (highVal != 0) for (int i = 0; i < valueList->size(); i++) valueList->at(i) /= highVal;
}

S getClassFromValue(double d) {
    S s;
    s.b = (d < 0.33334) ? 0 : (d < 0.66667) ? 1 : 2;
    return s;
}

vsb getClassifiedValues(dv valueList) {
    shiftNegative(&valueList);
    shrinkPositive(&valueList);
    vsb sv;
    for (double d : valueList) sv.push_back(getClassFromValue(d));    
    return sv;
}

vsb getValueList(string s) {	
    vmv moveList = getClassifyDataMove({4.53, 3.67, 8.91});
    ifstream f(s);
    string sline;
    dv valueList;
    vfp fv = getFunctions();
    while (f) if (getline(f, sline)) processLine(sline, moveList, fv, &valueList);
    for (auto& func : fv) delete func;
   
    return getClassifiedValues(valueList);
}

int main() {
    srand(time(0));
    vsb vs = getValueList("iris.data");
    for (S s : vs) cout<<s.b<<endl;    
    return 0;
}
