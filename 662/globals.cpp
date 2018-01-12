#include "globals.h"

Config_Registry armor_registry("armors.conf");
Config_Registry enemy_registry("enemies.conf");
Config_Registry item_registry("items.conf");
Config_Registry status_effect_registry("status_effects.conf");
Config_Registry weapon_registry("weapons.conf");

Player player;

int getRandomInt(int min, int max){
	max+=1;
	int range = max - min;
	double percentage = rand() / (double)RAND_MAX;
	int ans = (range * percentage) + min;
	if(ans == max)
		ans--;
	return ans;
}
int getRandomIndex(vector<int> relative_probablities){
	int total=0;
	for(int x : relative_probablities)
		total += x;

	total = getRandomInt(0,total);

	for(int x=0; x<relative_probablities.size(); x++){
		total -= relative_probablities[x];
		if(total<=0) return x;
	}

	return 0;
}