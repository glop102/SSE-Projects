#ifndef WEAPON
#define WEAPON

class Weapon;

#include "globals.h"

class Weapon{
public:
	struct Attack{
		string name;
		float power;
		float speed;
		string self_status_effect;
		string opponent_status_effect;
		string description;
		string usage_description;
	};
	string name;
	int damage;
	int damage_variance;
	int weight;
	string description;

	vector<Attack> attacks;
	Settings params;

	Weapon();
	Weapon(Settings params);
};

#endif