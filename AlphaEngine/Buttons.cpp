#include "Buttons.h"



dragdrop::dragdrop(double s1x, double s1y, double s2x, double s2y, bool flag, int refer)
{
	bounding.s1.x = s1x;
	bounding.s1.y = s1y;
	bounding.s2.x = s2x;
	bounding.s2.y = s2y;

	bounding.tr = bounding.s1;
	bounding.bl = bounding.s2;

	bounding.mid = midpoint(bounding.tr, bounding.bl);

	bounding.flag = flag;
	active = flag;
	ref = refer;

}

aabb dragdrop::getcoord() const
{
	return bounding;
}

int dragdrop::getref() const
{
	return ref;
}

bool dragdrop::getflag() const
{
	return active;
}

bool& dragdrop::flagchange(bool change)
{
	active = change;
	bounding.flag = change;
	return active;
}



dragdrop& dragdrop::move(double x, double y)
{
	bounding.tr.x += x;
	bounding.bl.x += x;
	bounding.mid.x += x;

	bounding.tr.y += y;
	bounding.bl.y += y;
	bounding.mid.y += y;
	return *this;
}


dragdrop& dragdrop::moveto(coord refer)
{
	bounding.tr.x += distance(bounding.mid, refer).x;
	bounding.tr.y += distance(bounding.mid, refer).y;

	bounding.bl.x += distance(bounding.mid, refer).x;
	bounding.bl.y += distance(bounding.mid, refer).y;

	bounding.mid.x = refer.x;
	bounding.mid.y = refer.y;


	return *this;
}

dragdrop& dragdrop::moveto(aabb refer)
{
	bounding.tr.x += distance(bounding.mid, refer.mid).x;
	bounding.tr.y += distance(bounding.mid, refer.mid).y;

	bounding.bl.x += distance(bounding.mid, refer.mid).x;
	bounding.bl.y += distance(bounding.mid, refer.mid).y;

	bounding.mid.x = refer.mid.x;
	bounding.mid.y = refer.mid.y;


	return *this;
}

aabb dragdrop::resetaabb()
{
	bounding.tr = bounding.s1; bounding.bl = bounding.s2;
	bounding.mid = midpoint(bounding.s1, bounding.s2);
	return bounding;
}

dragdrop::~dragdrop()
{}

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
		return 0;
	}
}

int aabbbutton(dragdrop* box, dragdrop* spell)
{
	aabb tmp = box->getcoord();
	aabb spl = spell->getcoord();
	if ((tmp.tr.x < spl.bl.x || tmp.bl.x > spl.tr.x)
		|| (tmp.tr.y < spl.bl.y || tmp.bl.y > spl.tr.y))
	{
		return spell->getref();
	}
	else
	{
		return -1;
	}
}

//Extra functions for main functions
coord midpoint(aabb box)
{
	coord tmp;
	tmp.x = (box.tr.x + box.bl.x) / 2.0;
	tmp.y = (box.tr.y + box.bl.y) / 2.0;
	return tmp;
}

coord midpoint(coord first, coord second)
{
	coord tmp;
	tmp.x = (first.x + second.x) / 2.0;
	tmp.y = (first.y + second.y) / 2.0;
	return tmp;
}

coord distance(coord first, coord second)
{
	coord tmp;
	tmp.x = first.x - second.x;
	tmp.y = first.y - second.y;
	return tmp;
}

double distance_diagonal(coord first, coord second)
{
	double d = 0.0;
	d = (first.x - second.x) * (first.x - second.x);
	d += (first.y - second.y) * (first.y - second.y);
	return sqrt(d);
}