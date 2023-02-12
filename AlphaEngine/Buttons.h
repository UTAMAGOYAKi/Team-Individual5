#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <iostream> // istream, ostream
#include <string.h>
#include <float.h>
#include <cmath>


struct coord {
	double x;	//the x-axis coordinate. Don't be funny on this part please
	double y;	//the y-axis coordinate
};

struct aabb {

	coord s1; //orignal top right
	coord s2; //original bot left
	coord mid;// middle of aabb
	coord tr; //active top right
	coord bl; //active bottom left
	bool flag;//usage flag, to check if current aabb is in use. 
};
class dragdrop {

public:
	//constructor

	dragdrop(double s1x, double s1y, double s2x, double s2y, bool flag, int refer);
	//constructor
	dragdrop() : bounding{ {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} } {};

	//	dragdrop(aabb box) : bounding{ box } {};
	//	dragdrop(coord _tr, coord _bl, bool _flag) : bounding{ _tr, _bl, _flag } {};

		//the get___() functions just return appropiate values for reference, planning or debugging
	aabb getcoord()const;
	int getref() const;
	bool getflag() const;

	//toggle the active flag, so it knows to check if it is currently active on screen 
	bool& flagchange(bool change); //bot.flagchange(true);




	//These functions use the middlepoint as the point it will move to
	dragdrop& moveto(coord refer);	// move the box to be on a point, mainly for the mouse	
	dragdrop& moveto(aabb refer);	//for centering a box on another box mainly
	dragdrop& move(double x_ref, double y_ref);	// simple translation


	/*
	This function resets the position to main original position in the game
	 i.e when doing spell combination, this will reset the location to where you
	 click on it to pick it up

	 Do note, say if you want to 'reset' back from the combined spell slot or another
	 sticky position, use move function with refer as the location it should be
	 */
	aabb resetaabb();



	//destructor
	~dragdrop();

private:
	aabb bounding;			//aabb/The box
	bool active{ false };	//bool to check if current is meant to be drawn/collidable on screen
	bool mouse{ false };	//bool to check if tagging on mouse
	int ref;				//This ref is mainly for the spell it refers to, for combination
};

//used to calculate the midpoint
coord midpoint(aabb box);
coord midpoint(coord first, coord second);

//For distance, x-axis and y-axis separately, do note that the distance can be negative, for ease of other functions
coord distance(coord first, coord second); // distance( thing, thang).y to get distance in y

//returns true distance. This is mainly for circle collision?
double distance_diagonal(coord first, coord second);

//checks for static collision of a point/ box with another box
//ref is return if true, -1 for false
int aabbbutton(dragdrop* box, coord mouse);
int aabbbutton(dragdrop* box, dragdrop* spell);

//std::istream& operator>> (std::istream is, dragdrop& box);


#endif // !BUTTON_HPP