#include "player.h"

player* player_create() // add 
{
	player* alchemist{ new player };

	if (0)	//file for info storage 
	{
		// get values from file
		// add values yadda dodda
	}
	else
	{
		std::cout << "No save found! Would you like to create a new save?\n";
		if (1) // get a input for choosing y/n
		{
			//creation of associated file

			alchemist->avail_ingre = 3;
			alchemist->hp = 30;

			std::cout << "New save created!\n";
		}
		else //no new save
		{

			alchemist->avail_ingre = -1; //illegal value / flag for exiting
			alchemist->hp = -999;

		}

	}

	return alchemist;
}


player_sit player_flag(player guy)
{
	if (guy.hp <= 0) // death check
	{
		return p_dead;
	}

	if (1) // normal attack check
	{
		return p_attack;
	}

	if (0) // alchemy check, however at current point, I cannot personally check, so zero
	{
		return p_alch;
	}


	return p_idle; // if no choice has been made, ie making up their mind, return them being idle
}
