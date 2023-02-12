#pragma once
#include <iostream>

enum player_sit { p_idle, p_attack, p_alch, p_status, p_dead };

struct player {

	int hp;
	int avail_ingre;

};

player* player_create();

player_sit player_flag(player guy);