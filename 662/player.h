#ifndef PLAYER
#define PLAYER

class Player;

#include "globals.h"

#include "armor.h"
#include "status_effect.h"
#include "weapon.h"

class Inventory{
public:
	vector<string> armor;
	vector<string> weapons;
	vector<string> items;
	map<string,vector<string> > other;
};

class Player{
	map<string,Armor*> armor;
	Weapon *weapon;
public:
	int max_health;
	int current_health;
	int speed;
	int money;
	int strength;
	vector<Status_Effect> status_effects;
	Inventory inventory;
	
	Player();

	Status_Effect getTotalStatusEffect(); //sums up all of the status effects and returns the combined result

	void setArmor(string name);
	string getArmorName(string category);

	void setWeapon(string name);
	string getWeaponName();

	int getCurrentStrength();
	int getCurrentSpeed();
	int getCurrentHealth();
	int getMaxHealth();
	int getCurrentArmor();

	void doDamage(int);

	void loadFromFile(string filename);
	void saveToFile(string filename);
};

#endif