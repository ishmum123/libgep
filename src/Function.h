#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <math.h>

class Function { public: virtual double run() = 0; };

class OneArgFunction : public Function {
public: OneArgFunction(double d1) : d1 (d1) {}
protected: double d1;
};

class DoNothingFunction : public OneArgFunction {
public: 
	DoNothingFunction(double d1) : OneArgFunction(d1) {}
	double run() { return d1; }
};

class InvertValueFunction : public OneArgFunction {
public:
	InvertValueFunction(double d1) : OneArgFunction(d1) {}
	double run() { return -d1; }
};

class LogFunction : public OneArgFunction {
public: 
	LogFunction(double d1) : OneArgFunction(d1) {}
	double run() { return log(d1); }
};

class TwoArgFunction : public Function {
public: TwoArgFunction(double d1, double d2) : d1 (d1), d2 (d2) {}
protected: double d1, d2;
};

class AddFunction : public TwoArgFunction { 
public: 
	AddFunction(double d1, double d2) : TwoArgFunction(d1, d2) {}
	double run() { return (d1 + d2); } 
};

class SubtractFunction : public TwoArgFunction { 
public: 
	SubtractFunction(double d1, double d2) : TwoArgFunction(d1, d2) {}
	double run() { return (d1 - d2); } 
};

class MultiplyFunction : public TwoArgFunction { 
public: 
	MultiplyFunction(double d1, double d2) : TwoArgFunction(d1, d2) {}
	double run() { return (d1 * d2); } 
};

class DivideFunction : public TwoArgFunction { 
public: 
	DivideFunction(double d1, double d2) : TwoArgFunction(d1, d2) {}
	double run() { return (d1 / d2); } 
};

class FunctionFactory {
	
};

#endif
