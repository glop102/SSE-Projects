#include "item.h"

Item::Item(){
	name = "unknown";
	value = 1;
	consumable = true;
	self_status_effect = "None";
	opponent_status_effect = "None";
}

Item::Item(Settings params){
	this->params = params;
	name = params.getValueAsString("name","unknown");
	value = params.getValueAsInt("value",1);
	consumable = params.getValueAsInt("consumable",true);
	self_status_effect = params.getValueAsString("self status effect","None");
	opponent_status_effect = params.getValueAsString("opponent status effect","None");
}