#include "config_registry.h"

Config_Registry::Config_Registry(string filename){
	items = GlopConfig::ParseFile(filename);

	auto itt = items.groups.begin();
	while(itt != items.groups.end()){
		names.push_back(itt->first);
		itt++;
	}
}
vector<string> Config_Registry::getNames(){
	return names;
}

Settings Config_Registry::getParams(string name){
	if(items.groups.count(name) == 0){
		return Settings();
	}
	return items.groups.at(name); // uses the .at() so that it will throw an error to the user
}