#include "Map.h"


int map_movement(int current)
{
	dragdrop next;
	next.changeaabb(10.0, 10.0);
	AEVec2 middle {0 ,0 };
	next.moveto(middle);
	
	if (current == 4)//boss?
	{

	}
	else
	{
		for (int i = 0; i < current; i++)
		{
			//draw texture of previous level, if any
		}
	}



	return 0;
}