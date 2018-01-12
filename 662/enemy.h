#ifndef ENEMY
#define ENEMY

class Enemy;

#include "globals.h"
#include "status_effect.h"

class Enemy{
	string name;

	int max_health;
	int current_health;
	int speed;
	int armor;
	int strength;

	int money;
	int exp;
public:
	struct Attack{
		string name;
		float power;
		float speed;
		int relative_probability;
		string self_status_effect;
		string opponent_status_effect;
		string description;
		string usage_description;
	};

	vector<Attack> attacks;
	vector<Status_Effect> status_effects;
	Settings params;

	Enemy();
	Enemy(Settings params);

	int getCurrentStrength();
	int getCurrentSpeed();
	int getCurrentHealth();
	int getMaxHealth();
	int getCurrentArmor();
	int getMoney();
	int getEXP();
	Attack getRandomAttack();
	string getName();

	void doDamage(int);
};

#endif