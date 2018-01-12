#ifndef GLOBALS
#define GLOBALS

#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <map>
#include "glopConfig.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::map;
using std::pair;
using GlopConfig::Settings;

int getRandomInt(int min, int max); // a simple and tested way for you to get a random int from a given range
int getRandomIndex(vector<int> relative_probablities); // example - if given [3,2,6], will choose first index 3 out of 11 times, returning a zero

#include "config_registry.h"

extern Config_Registry armor_registry;
extern Config_Registry enemy_registry;
extern Config_Registry item_registry;
extern Config_Registry status_effect_registry;
extern Config_Registry weapon_registry;

#include "player.h"

extern Player player;

#endif