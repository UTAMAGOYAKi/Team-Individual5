#include "Map.h"


int map_movement(int current, AEVec2 mouse)
{
	dragdrop next;
	next.changeaabb(10.0, 10.0);
	AEVec2 middle {0 ,0 };
	next.moveto(middle);
	

	if (aabbbutton(&next, mouse))
	{
		return (current + 1);
		// lead into the next level
	}

	return 0;
}