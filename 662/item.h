#ifndef ITEM
#define ITEM

class Item;

#include "globals.h"

class Item{
public:
	string name;
	int value;
	bool consumable;
	string self_status_effect;
	string opponent_status_effect;

	Settings params;

	Item();
	Item(Settings params);
};

#endif