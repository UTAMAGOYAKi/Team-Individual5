/******************************************************************************/
/*!
\file		EnemyObject.h
\author 	Yeo Jun Jie
\par    	email: yeo.junjie\@digipen.edu
\brief		Enemy class declaration and its member functions and functions.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#define TOTAL_ENEMY 3
const int animation_time = 1;

//Element Icons
//AEGfxTexture * fire_icon, * water_icon, * poison_icon, * shadow_icon;

enum class enemy_types 
{
    base_rat,
    big_rat
};

enum enemy_life_state_enum 
{
    dead = 0,
    alive,
};

class Enemy
{
private:
    std::string name{};
    int max_hp{};
    int hp{};
    int atk{};
    Elements element_type{};

    //______________________ENEMY PLACEMENTS_________________________
    AEVec2 pos{};
    AEVec2 element_icon_pos{};
    AEGfxTexture* icon_texture{};
    AEGfxTexture* texture{}; 
    int size = 1; //pixel size for AABB
    aabb enemy_aabb{};

    //________________________ENEMY COMBAT SETTINGS____________________________
    bool life_state{alive}; //Uses enemy_life_state: either dead or alive
    bool finish_attack{ false };
               
  //________________________FOR ANIMATIONS____________________________
  //Setting
    int total_frame = 4;
    int frame_num = 0; //current frame
    double attack_animation_timer = .3f;

    //Frame times
    double frame_time = attack_animation_timer / (double)total_frame;
    double frame_timer = frame_time;

    //Bleed Time
    bool bleeding{false};
    f64 bleed_time{0.8f};
    f64 bleed_timer{bleed_time};

    //Damage Number
    std::string str_damage_number{};

    AEVec2 default_str_damage_pos{}; 
    AEVec2 str_damage_pos{};
    AEVec2 str_damage_pos_percent{};
    
    bool bool_damage_num{ false };
    float damage_time{ 1.0f };
    float damage_timer{damage_time};
    float crit_colour{ 1.0f };
    
    //_______________________FOR AUDIO_______________________________
    bool audio{ false };

    //_________________FOR DAMAGE NUMBER DEALT TO PLAYER_____________
    AEVec2 p_default_damage_num_pos{ -320.f,0.0f };
    AEVec2 p_damage_num_pos{ p_default_damage_num_pos };
    AEVec2 p_damage_num_percent_pos{};
    std::string p_damage_num_str{};

    bool p_bool_damage_num{ false };
    float p_damage_time{ 1.0f };
    float p_damage_timer{ damage_time };

public:
    Enemy() {};

    Enemy(enemy_types type, AEGfxTexture* input_texture, std::string input_name, int input_hp, int input_atk, Elements element) 
        : texture{ input_texture }, life_state{alive} , name{input_name}, max_hp{ input_hp }, atk{input_atk}, element_type{element}
    {
        hp = max_hp; //Initialized hp will be same as max_hp;

        //Sets icon
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
    AEVec2 get_element_icon_pos();
    Elements get_element();
    std::string get_str_damage_number();
    AEVec2 get_str_damage_pos_percent();
    bool get_bool_damage_num();
    float get_crit_colour();
    
    //Used to make changes to damage classes.
    void set_position_and_aabb(AEVec2 input_pos);
    void take_damage(int val, Elements element);
    int elemental_damage_calculator(Elements enemy_type, Elements input_element);
    void set_frame_num(int);        //Changes the frame number for the update animation
    void update_animation(f64 dt); //Updates the frame number to draw the correct frame.
    void switch_finish_attack();      //switches true to false or false to true;

    //void create_particle(std::vector<particle>& particle_vector, int particle_max);
    void set_bleeding(bool logic);
    void update_bleed_timer();
    void reset_bleed_time();

    //Damage Numbers
    AEVec2 convert_pos(AEVec2 input_pos);
    void update_damage_timer();
    void set_crit_colour(bool input);

    //Audio
    bool get_audio();
    void set_audio(bool input);

    //_______________ENEMY DAMAGE ONTO PLAYER NUM____________________
    void set_p_damage_num_pos(AEVec2 const& input);

    AEVec2 get_p_damage_num_percent_pos();
    std::string get_p_damage_num_str();
    bool get_p_bool_damage_num();

    void set_p_bool_damage_num(bool input);
    void set_p_damage_num_str(std::string input);
    void update_p_damage_timer();
};

#endif // ENEMY_H