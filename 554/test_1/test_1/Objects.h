#pragma once
class SimpleClass {
public:
	SimpleClass() {}
	virtual ~SimpleClass() {}

	void onlyLocallyOverridable() {}
	virtual void overridenIfASubclassWants() {}
};