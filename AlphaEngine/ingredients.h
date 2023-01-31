

#ifndef igredients_h
#define igredients_h

struct structspells;


#include <string>
#include <vector>
enum ingredients {
    FIRE,
    WATER,
    ELECTRIC,
    POISON,
    FREEZE,
    WIND,
    NILL
};

enum position {
    outside,
    onscreen,
    slotted,
    comb_slotted,
    mouse
};


struct ingre_pos {

    float x;
    float y;
    int use;
};


struct ingre_info {
    structspells* iden;
    ingre_pos* pos;
    int dmg;
};

struct caldron {
    ingre_pos slot[3];
    int num_slots;
    ingre_pos place;

};

ingre_info* create_ingredients();


#endif // !1
