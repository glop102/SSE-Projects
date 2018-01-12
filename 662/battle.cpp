#include "battle.h"

Battle::Battle(){
	p=NULL;
	e=NULL;
}
Battle::Battle(Player& p, Enemy& e){
	this->p = &p;
	this->e = &e;
}
void Battle::startBattle(){
	battle_over=false;
	while(!battle_over){
		printBattleStatus();
		ACTION a = getPlayerTurnAction();
		if(a == FIGHT){
			pair<int,Weapon::Attack> pattack = getPlayerAttack();
			int pspeed = p->getCurrentSpeed() * pattack.second.speed;
			int parmor = p->getCurrentArmor();
			int pstrength = p->getCurrentStrength() * pattack.first * pattack.second.power;
			Enemy::Attack eattack = e->getRandomAttack();
			int espeed = e->getCurrentSpeed() * eattack.speed;
			int earmor = e->getCurrentArmor();
			int estrength = e->getCurrentStrength() * eattack.power;

			if(pspeed>espeed){
				cout << pattack.second.usage_description +"\n";
				e->doDamage(pstrength - earmor);
				if(e->getCurrentHealth()>0){
					cout << eattack.usage_description +"\n";
					p->doDamage(estrength - parmor);
				}
			}else{
				cout << eattack.usage_description +"\n";
				p->doDamage(estrength - parmor);
				if(p->getCurrentHealth()>0){
					cout << pattack.second.usage_description +"\n";
					e->doDamage(pstrength - earmor);
				}
			}
		}else if(a == USE_ITEM){

		}else if(a == RUN){
			break;
		}
	}
}
void Battle::printBattleStatus(){
	cout<<"========================================================================\n";
	int num_chars;
	int bar_width = 30;

	//Monster Info
	printf("%s speed %d : %d strength\n" , e->getName().c_str(),e->getCurrentSpeed(),e->getCurrentStrength());
	printf("\tHP %5d ",e->getCurrentHealth());
		num_chars = (e->getCurrentHealth()/(float)e->getMaxHealth()) * bar_width;
		for(int x=0; x<num_chars; x++) printf("#");
	printf("\n");

	//Player Info
	printf("Player speed %d : %d strength\n",p->getCurrentSpeed(),p->getCurrentStrength());
	printf("\tHP %5d ",p->current_health);
		num_chars = (p->current_health/(float)p->max_health) * bar_width;
		for(int x=0; x<num_chars; x++) printf("#");
	printf("\n");
}

Battle::ACTION Battle::getPlayerTurnAction(){
	int choice=-1;
	while(choice<0 || choice>RUN){
		printf("1. Fight\n");
		printf("2. Use Item\n");
		printf("3. Run\n");
		cin >> choice;
		choice -= 1;
	}
	return (ACTION)choice;
}
pair<int,Weapon::Attack> Battle::getPlayerAttack(){
	Weapon w(weapon_registry.getParams(p->getWeaponName()));
	if(w.attacks.size() == 0)
		return pair<int,Weapon::Attack>(1,Weapon::Attack());
	int choice=-1;
	while(choice<0 || choice>=w.attacks.size()){
		for(int x=0; x<w.attacks.size(); x++){
			printf("%d. %s\n  : speed %f : %f power",
				x+1,w.attacks[x].name.c_str(),w.attacks[x].speed,w.attacks[x].power);
		}
		cin >> choice;
		choice--;
	}
	return pair<int,Weapon::Attack>(w.damage+getRandomInt(0,w.damage_variance), w.attacks[choice]);
}

void Battle::winAction(){
	//do what you want to give rewards
	//like get the money from the enemy 
}
void Battle::loseAction(){
}