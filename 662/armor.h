#ifndef ARMOR
#define ARMOR

class Armor;

#include "globals.h"

class Armor{
public:
	string name;
	string category;
	int weight;
	int defense;
	int value;

	Settings params;
	
	Armor();
	Armor(Settings params);
};

#endif