#include "weapon.h"

Weapon::Weapon(){
	name = "Dummy Weapon";
	damage = 1;
	damage_variance = 0;
}

Weapon::Weapon(Settings params){
	this->params = params;
	name = params.getValueAsString("name","unknown");

	damage = params.getValueAsInt("damage",1);
	damage_variance = params.getValueAsInt("damage variance",1);
	weight = params.getValueAsInt("weight",1);

	description = params.getValueAsString("description","None provided");

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

			attacks.push_back(a);
			itt++;
		}
	}
}