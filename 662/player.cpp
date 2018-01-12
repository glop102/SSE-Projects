#include "player.h"

Player::Player(){
	max_health = 1;
	current_health = 1;
	speed = 1;
	money = 0;
	strength = 1;
	weapon = new Weapon();
}

void Player::setArmor(string name){
}
string Player::getArmorName(string category){
	if(armor.count(category) == 0)
		return "None";
	else
		return armor.at(category)->name;
}

void Player::setWeapon(string name){
}
string Player::getWeaponName(){
	return weapon->name;
}

int Player::getCurrentStrength(){
	Status_Effect s;
	for(auto x : status_effects)
		s+=x;
	return strength * (1.0 + s.strength_multiplier) + s.strength_addition;
}
int Player::getCurrentSpeed(){
	Status_Effect s;
	for(auto x : status_effects)
		s+=x;
	return speed * (1.0 + s.speed_multiplier) + s.speed_addition;
}
int Player::getCurrentHealth(){
	return current_health;
}
int Player::getMaxHealth(){
	Status_Effect s;
	for(auto x : status_effects)
		s+=x;
	return max_health * (1.0 + s.health_multiplier) + s.health_addition;
}
int Player::getCurrentArmor(){
	int a=0;
	for(auto itt : armor){
		a += itt.second->defense;
	}
	return a;
}

void Player::doDamage(int amount){
	current_health -= amount;
	if(current_health>getMaxHealth())
		current_health = getMaxHealth();
}