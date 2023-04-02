/******************************************************************************/
/*!
\file		Player.h
\project	Alchemice
\author 	Daniel Tee(95%), Liang HongJie(5%)
\par    	email: m.tee\@digipen.edu, l.hongjie\@digipen.edu 
\brief		Struct for the player and declarations of functions used to create 
			the player.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#pragma once
#include <iostream>



struct player {
	int hp;
	int max_hp;
	int avail_ingre;
	int mp;
	int max_mp;
};

player* create_player();
void delete_player(player* ptr);
