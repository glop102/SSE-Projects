#include "globals.h"
#include "armor.h"
#include "enemy.h"
#include "item.h"
#include "status_effect.h"
#include "weapon.h"
#include "battle.h"
#include "player.h"

int main(){
	srand(time(NULL));
	for(auto x : enemy_registry.getNames()){
		cout<<"Fighting a "<<x<<"\n";
		Enemy e(enemy_registry.getParams(x));
		Battle battle(player,e);
		battle.startBattle();
	}
	
	// Status_Effect a(status_effect_registry.getParams("Intimidate"));
	// Status_Effect b(status_effect_registry.getParams("Intimidate"));
	// a = a+b;
	// printf("%f\n", a.speed_multiplier);

	// vector<int> p;
	// p.push_back(3);
	// p.push_back(2);
	// p.push_back(6);
	// int counter[4]={0,0,0,0};
	// for(int x=0; x<11000; x++)
	// 	counter[getRandomIndex(p)]++;
	// printf("%d %d %d %d\n",counter[0],counter[1],counter[2],counter[3]);

	return 0;
}