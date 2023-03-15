#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

//Unused currently
#include "Main.h"
#include "string"
#include "Buttons.h"
#include <AEVec2.h>

#define TOTAL_ENEMY 3
const int animation_time = 1;

enum enemy_types 
{
    base_rat,
    big_rat
};

enum enemy_life_state_enum 
{
    dead = 0,
    alive,
};

struct particle
{
    AEVec2 position;
    AEVec2 velocity;
    f64 lifespan;
    float size;
};

class Enemy
{
private:
    std::string name;
    int max_hp;
    int hp;
    int atk;
    AEVec2 pos;
    AEGfxTexture* texture;
    int size = 1; //pixel size for AABB
    aabb enemy_aabb;

    //________________________ENEMY COMBAT SETTINGS____________________________
    bool life_state{alive}; //Uses enemy_life_state: either dead or alive
    bool finish_attack{ false };
               
  //________________________FOR ANIMATIONS____________________________
  //Setting
    int total_frame = 4;
    int frame_num = 0; //current frame
    double attack_animation_timer = 1.0f;

    //Frame times
    double frame_time = attack_animation_timer / (float)total_frame;
    double frame_timer = frame_time;

    //Bleed Time
    bool bleeding{false};
    float bleed_time{2.0f};
    f64 bleed_timer{bleed_time};
    
public:
    Enemy(){};

    Enemy(enemy_types type, AEGfxTexture* input_texture, std::string input_name, int input_hp, int input_atk) 
        : texture{ input_texture }, life_state{alive} , name{input_name}, atk{input_atk}, max_hp{input_hp}
    {
        hp = max_hp; //Initialized hp will be same as max_hp;
    };

    ~Enemy() {};//deconstructor
    //Member functions
    
    //Used to retrieve data from class
    std::string get_name();
    int get_max_hp();
    int get_hp();
    int get_atk();
    AEVec2 get_pos();
    AEGfxTexture* get_texture();
    bool is_alive();
    int get_frame_num();
    aabb get_aabb();
    int get_total_frame();
    bool get_finish_attack();
    bool is_bleeding();
    f64 get_bleed_timer();
    
    //Used to make changes to damage classes.
    void set_position_and_aabb(AEVec2 input_pos);
    void take_damage(int val);
    void set_frame_num(int);        //Changes the frame number for the update animation
    void update_animation(f64 dt); //Updates the frame number to draw the correct frame.
    void switch_finish_attack();      //switches true to false or false to true;

    void create_particle(std::vector<particle>& particle_vector, int particle_max);
    void set_bleeding(bool logic);
    void update_bleed_timer();
    void reset_bleed_time();
};

//Particles
void update_particle();

#endif // ENEMY_H