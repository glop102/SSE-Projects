#ifndef BATTLE
#define BATTLE

class Battle;

#include "globals.h"

#include "enemy.h"
#include "player.h"

class Battle{
	Player *p;
	Enemy *e;
	bool playerHasWon;
	enum ACTION{FIGHT,USE_ITEM,RUN};
	bool battle_over;
public:
	Battle();
	Battle(Player& p,Enemy& e);

	void startBattle();
	void printBattleStatus();
	ACTION getPlayerTurnAction();
	pair<int,Weapon::Attack> getPlayerAttack(); // returns damage and the attack

	void winAction();
	void loseAction();
};

#endif