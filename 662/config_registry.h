#ifndef CONFIG_REGISTRY
#define CONFIG_REGISTRY

class Config_Registry;

#include "globals.h"

class Config_Registry{
	Settings items;
	vector<string> names;
public:
	Config_Registry(string filename);
	vector<string> getNames();
	Settings getParams(string name);
};

#endif