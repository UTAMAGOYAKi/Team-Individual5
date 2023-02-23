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

bool dragdrop::getmouse() const
{
	return mouse;
}

bool& dragdrop::flagchange(bool change)
{
	active = change;
	bounding.flag = change;
	return active;
}

bool& dragdrop::mousechange(bool change)
{
	mouse = change;
	return active;
}

dragdrop& dragdrop::changeref(int num)
{
	ref = num;
	return *this;
}


dragdrop& dragdrop::changeaabb(double width, double height)
{
	bounding.s1.x += width / 2;
	bounding.s1.y += height / 2;

	bounding.s2.x -= width / 2;
	bounding.s2.y -= height / 2;

	bounding.tr = bounding.s1;
	bounding.bl = bounding.s2;

	return *this;
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


dragdrop& dragdrop::moveto(AEVec2 refer)
{
	bounding.tr.x -= distance(bounding.mid, refer).x;
	bounding.tr.y += distance(bounding.mid, refer).y;

	bounding.bl.x -= distance(bounding.mid, refer).x;
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

int aabbbutton(dragdrop* box, AEVec2 mouse)
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
	if ((tmp.tr.x <= spl.bl.x && tmp.bl.x >= spl.tr.x)
		|| (tmp.tr.y <= spl.bl.y && tmp.bl.y >= spl.tr.y))
	{
		return spell->getref();
	}
	else
	{
		return -1;
	}
}

int aabbbutton(dragdrop* spell, aabb box)
{
	aabb tmp = spell->getcoord();
	if ((tmp.tr.x<box.bl.x || tmp.bl.x>box.tr.x)
		|| (tmp.tr.y < box.bl.y || tmp.bl.y>box.tr.y))
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

//Extra functions for main functions
AEVec2 midpoint(aabb box)
{
	AEVec2 tmp;
	tmp.x = (box.tr.x + box.bl.x) / 2.0;
	tmp.y = (box.tr.y + box.bl.y) / 2.0;
	return tmp;
}

AEVec2 midpoint(AEVec2 first, AEVec2 second)
{
	AEVec2 tmp;
	tmp.x = (first.x + second.x) / 2.0;
	tmp.y = (first.y + second.y) / 2.0;
	return tmp;
}

AEVec2 distance(AEVec2 first, AEVec2 second)
{
	AEVec2 tmp;
	tmp.x = first.x - second.x;
	tmp.y = first.y - second.y;
	return tmp;
}

double distance_diagonal(AEVec2 first, AEVec2 second)
{
	double d = 0.0;
	d = (first.x - second.x) * (first.x - second.x);
	d += (first.y - second.y) * (first.y - second.y);
	return sqrt(d);
}


#include "Main.h"

AEVec2 enemy_position[3];
AEVec2 player_position;

void PositionInit() {

	player_position.x = (float)(-(AEGetWindowWidth() / 4));
	player_position.y = 0;// (float)-(AEGetWindowHeight() / 8);
	enemy_position[0].x = (float)((9.0 / 16.0) * (AEGetWindowWidth() / 2));
	enemy_position[0].y = 0;
	enemy_position[1].x = (float)((6.0 / 16.0) * (AEGetWindowWidth() / 2));
	enemy_position[1].y = 0;
	enemy_position[2].x = (float)((12.0 / 16.0) * (AEGetWindowWidth() / 2));
	enemy_position[2].y = 0;
}


