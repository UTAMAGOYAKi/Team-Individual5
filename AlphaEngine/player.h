#pragma once
#include <iostream>

enum player_sit { p_idle, p_attack, p_alch, p_status, p_dead };

struct player {
	int hp;
	int max_hp;
	int avail_ingre;
	int mp;
	int max_mp;
};

player* create_player();
void delete_player(player* ptr);

player_sit player_flag(player guy);