#include "status_effect.h"

Status_Effect::Status_Effect(){
	name = "unknown";
	speed_multiplier = 0.0;
	health_multiplier = 0.0;
	strength_multiplier = 0.0;
	speed_addition = 0;
	health_addition = 0;
	strength_addition = 0;
	removed_after_fight = false;
	applied_every_turn = false;
	num_turns_left = -1;
}
Status_Effect::Status_Effect(Settings params){
	this->params = params;
	name = params.getValueAsString("name","unknown");
	speed_multiplier = params.getValueAsDouble("speed multiplier",1.0);
	health_multiplier = params.getValueAsDouble("health multiplier",1.0);
	strength_multiplier = params.getValueAsDouble("strength multiplier",1.0);
	speed_addition = params.getValueAsInt("speed addition",0);
	health_addition = params.getValueAsInt("health addition",0);
	strength_addition = params.getValueAsInt("strength addition",0);
	removed_after_fight = params.getValueAsBool("removed after fight",false);
	applied_every_turn = params.getValueAsBool("applied every turn",false);
	num_turns_left = params.getValueAsInt("number turns of effect",-1);
}
Status_Effect& Status_Effect::operator+=(const Status_Effect &rhs){
	speed_multiplier += rhs.speed_multiplier;
	speed_addition += rhs.speed_addition;
	health_multiplier += rhs.health_multiplier;
	health_addition += rhs.health_addition;
}
Status_Effect operator+(Status_Effect lhs,const Status_Effect& rhs){
	lhs += rhs;;
	return lhs;
}