

#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <iostream> // istream, ostream
#include <string.h>
#include <float.h>

namespace Inputs {

struct coord {
		double x;
		double y;
};

struct aabb {

	coord s1; //orignal top right
	coord s2; //original bot left
	coord tr; //active top right
	coord bl; //active bottom left
	bool flag;//usage flag
};
class dragdrop {

public:

	dragdrop() : bounding{ {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} }  {};
//	dragdrop(aabb box) : bounding{ box } {};
//	dragdrop(coord _tr, coord _bl, bool _flag) : bounding{ _tr, _bl, _flag } {};

	aabb getcoord() { return bounding; }
	int getref() { return ref; };
	bool getflag() { return active; };
	bool& flagchange() {}; //bot.flagchange() = true;
	

	//dragdrop = new dragdrop({ {0.0, 0.0}, {0.0, 0.0}, false });
	aabb& resetaabb() { this->bounding.tr = this->bounding.s1; this->bounding.bl = this->bounding.s2; };

private:
	aabb bounding;
	bool active{ false };
	int ref;
};



int aabbbutton(dragdrop* box, coord mouse);
int aabbbutton(dragdrop* box, dragdrop* spell);

//std::istream& operator>> (std::istream is, dragdrop& box);







}







#endif // !BUTTON_HPP
