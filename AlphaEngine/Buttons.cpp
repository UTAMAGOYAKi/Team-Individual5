#include "Buttons.hpp"

namespace Inputs {

	int aabbbutton(dragdrop* box, coord mouse)
	{
		aabb tmp = box->getcoord();
		if (
			(tmp.bl.x < mouse.x && mouse.x < tmp.tr.x)
			&&
			(tmp.bl.y < mouse.y && mouse.y < tmp.tr.y)
			)
		{
			return box->getref();
		}
		else
		{
			return -1;
		}
	}

	int aabbbutton(dragdrop* box, dragdrop* spell)
	{
		aabb tmp = box->getcoord();
		aabb spl = spell->getcoord();
		if ((tmp.tr.x < spl.bl.x || tmp.bl.x > spl.tr.x)
	 	||  (tmp.tr.y < spl.bl.y || tmp.bl.y > spl.tr.y))
		{
			return spell->getref();
		}
		else
		{
			return -1;
		}
	}

	




}