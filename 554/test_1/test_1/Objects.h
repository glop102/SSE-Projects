#pragma once
#include "stdafx.h"

using std::string;

class Base1 {
public:
	string name();
};
class Sub1:public Base1 {
public:
	string name();
};

class Base2 {
public:
	virtual string name();
};
class Sub2 :public Base2 {
public:
	string name();
};

class Base3 {
public:
	static string name();
};
class Sub3 :public Base3 {};

class SummaryClass {
public:
	SummaryClass() {}
	virtual ~SummaryClass() {}

	void onlyLocallyOverridable() {}
	virtual void overridenIfASubclassWants() {}
	virtual void forcedToOverrideThis() = 0;

	static void globalToAllObjectThatInherit() {}
};