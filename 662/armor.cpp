#include "armor.h"

Armor::Armor(){
	name = "Dummy Armor";
	category = "None";
	weight = 1;
	defense = 1;
	value = 1;
}

Armor::Armor(Settings params){
	this->params = params;
	name = params.getValueAsString("name","unknown");
	category = params.getValueAsString("name","unknown");
	weight = params.getValueAsInt("weight",1);
	defense = params.getValueAsInt("defense",1);
	value = params.getValueAsInt("value",1);
}