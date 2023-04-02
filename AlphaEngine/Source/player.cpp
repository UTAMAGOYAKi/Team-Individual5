/******************************************************************************/
/*!
\file		Player.cpp
\project	Alchemice
\author 	Daniel Tee(95%), Liang HongJie(5%)
\par    	email: m.tee\@digipen.edu, l.hongjie\@digipen.edu
\brief		Functions definition associated player struct

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "Player.h"

player* create_player() // add 
{
	player* alchemist{ new player };
	if (0)	//file for info storage 
	{
		// get values from file
		// add values yadda dodda
	}
	else
	{
		if (1) // get a input for choosing y/n
		{
			//creation of associated file
			alchemist->avail_ingre = 3;
			alchemist->max_hp = 30;
			alchemist->hp = 30;
			alchemist->mp = 2;
			alchemist->max_mp = 2;
		}
		else //no new save
		{
			alchemist->avail_ingre = -1; //illegal value / flag for exiting
			alchemist->hp = -999;
		}
	}
	return alchemist;
}

void delete_player(player* player_ptr) {
	delete player_ptr;
}



