#ifndef STATUS_EFFECT
#define STATUS_EFFECT

class Status_Effect;

#include "globals.h"

class Status_Effect{
public:
	string name;
	float speed_multiplier;
	float health_multiplier;
	float strength_multiplier;
	int speed_addition;
	int health_addition;
	int strength_addition;
	bool removed_after_fight;
	bool applied_every_turn;
	int num_turns_left; // if negative, then never remove

	Settings params;
	
	Status_Effect();
	Status_Effect(Settings params);
	Status_Effect& operator+=(const Status_Effect& rhs);
	friend Status_Effect operator+(Status_Effect lhs,const Status_Effect& rhs); // fill out to allow simply adding effects so we can have a grand total effect to apply to our character
};

#endif