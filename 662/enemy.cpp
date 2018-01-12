#include "enemy.h"

Enemy::Enemy(){
	name = "Dummy Enemy";
	max_health = 1;
	current_health = 1;
	speed = 1;
	armor = 1;
	strength = 1;
	money = 1;
	exp = 1;
}

Enemy::Enemy(Settings params){
	this->params = params;
	name = params.getValueAsString("name","unknown");

	max_health = params.getValueAsInt("base health",1);
	max_health += getRandomInt( 0, params.getValueAsInt("health variance",1) );
	current_health = max_health;

	speed = params.getValueAsInt("base speed",1);
	speed += getRandomInt( 0, params.getValueAsInt("speed variance",1) );

	armor = params.getValueAsInt("base armor",1);
	armor += getRandomInt( 0, params.getValueAsInt("armor variance",1) );

	strength = params.getValueAsInt("base strength",1);
	strength += getRandomInt( 0, params.getValueAsInt("strength variance",1) );

	money = params.getValueAsInt("base money",1);
	money += getRandomInt( 0, params.getValueAsInt("money variance",1) );
	
	exp = params.getValueAsInt("base exp",1);
	exp += getRandomInt( 0, params.getValueAsInt("exp variance",1) );

	if(params.groups.count("attacks")){
		auto itt = params.groups.at("attacks").groups.begin();
		while(itt != params.groups.at("attacks").groups.end()){
			Settings attack_params = itt->second;
			Attack a;
			a.name = itt->first;
			a.self_status_effect = attack_params.getValueAsString("self status effect","None");
			a.opponent_status_effect = attack_params.getValueAsString("opponent status effect","None");
			a.description = attack_params.getValueAsString("description","None provided");
			a.usage_description = attack_params.getValueAsString("usage description","attacked by "+a.name);
			a.power = attack_params.getValueAsDouble("power",1);
			a.speed = attack_params.getValueAsDouble("speed",1);
			a.relative_probability = attack_params.getValueAsInt("relative probability",1);

			attacks.push_back(a);
			itt++;
		}
	}
}

int Enemy::getCurrentStrength(){
	Status_Effect s;
	for(auto x : status_effects)
		s+=x;
	return strength * (1.0 + s.strength_multiplier) + s.strength_addition;
}
int Enemy::getCurrentSpeed(){
	Status_Effect s;
	for(auto x : status_effects)
		s+=x;
	return speed * (1.0 + s.speed_multiplier) + s.speed_addition;
}
int Enemy::getCurrentHealth(){
	return current_health;
}
int Enemy::getMaxHealth(){
	Status_Effect s;
	for(auto x : status_effects)
		s+=x;
	return max_health * (1.0 + s.health_multiplier) + s.health_addition;
}
int Enemy::getCurrentArmor(){
	return armor;
}
int Enemy::getMoney(){
	return money;
}
int Enemy::getEXP(){
	return exp;
}
Enemy::Attack Enemy::getRandomAttack(){
	if(attacks.size() == 0){
		Attack a;
		a.power = 1.0;
		a.speed = 1.0;
		a.usage_description = name+" tries to tackle you";
		return a;
	}
	vector<int> probs;
	probs.reserve(attacks.size());
	for(auto a : attacks)
		probs.push_back(a.relative_probability);
	int index = getRandomIndex(probs);
	return attacks[index];
}
string Enemy::getName(){
	return name;
}

void Enemy::doDamage(int amount){
	current_health -= amount;
	if(current_health>getMaxHealth())
		current_health = getMaxHealth();
}