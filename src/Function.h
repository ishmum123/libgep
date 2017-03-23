#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <iostream>
#include <math.h>

class Function { public: virtual double run() = 0; };

class OneArgFunction : public Function {
protected: double d1;
public: 
	void initiate(double d1) { 
		this->d1 = d1; 
	}
};

class DoNothingFunction : public OneArgFunction {
public: double run() { return d1; }
};

class InvertValueFunction : public OneArgFunction {
public: double run() { return -d1; }
};

class LogFunction : public OneArgFunction {
public: double run() { return log(d1); }
};

class TwoArgFunction : public Function {
protected: double d1, d2;
public: 
	void initiate(double d1, double d2) {
		this->d1 = d1;
		this->d2 = d2;
	}
};

class AddFunction : public TwoArgFunction { 
public: double run() { return (d1 + d2); } 
};

class SubtractFunction : public TwoArgFunction { 
public: double run() { return (d1 - d2); } 
};

class MultiplyFunction : public TwoArgFunction { 
public: double run() { return (d1 * d2); } 
};

class DivideFunction : public TwoArgFunction { 
public: double run() { return (d1 / d2); } 
};

class FunctionFactory {
public:
	OneArgFunction * getOneArgFunction(int i) {
		switch (i) {
			case 0: return new DoNothingFunction();
			case 1: return new InvertValueFunction();
			case 2: return new LogFunction();
			default: throw -1;
		}
	}
	TwoArgFunction * getTwoArgFunction(int i) {
		switch (i) {
			case 0: return new AddFunction();
			case 1: return new SubtractFunction();
			case 2: return new MultiplyFunction();
			case 3: return new DivideFunction();
			default: throw -1;
		}
	}
	int getNumOfOneArgFunction() { return 3; }
	int getNumOfTwoArgFunction() { return 4; }
};

//OneArgFunction * FunctionFactory::getOneArgFunction(int i)

//TwoArgFunction * FunctionFactory::getTwoArgFunction(int i)

#endif
