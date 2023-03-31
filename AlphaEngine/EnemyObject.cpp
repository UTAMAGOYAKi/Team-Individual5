/******************************************************************************/
/*!
\file		EnemyObject.cpp
\author 	Yeo Jun Jie
\par    	email: yeo.junjie\@digipen.edu
\brief		Member functions and functions for Enemy objects

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "EnemyObject.h"
#include "Buttons.h"

//Functions to retrieve Enemy datas
std::string Enemy::get_name() {
    return name;
}

int Enemy::get_max_hp() {
    return max_hp;
}

int Enemy::get_hp() {
    return hp;
}

int Enemy::get_atk() {
    return atk;
}

AEVec2 Enemy::get_pos() {
    return pos;
}

AEGfxTexture* Enemy::get_texture() {
    return texture;
}

bool Enemy::is_alive() {
    return life_state;
}

aabb Enemy::get_aabb()
{
    return  enemy_aabb;
}

int Enemy::get_frame_num() {
    return frame_num;
}

int Enemy::get_total_frame() {
    return total_frame;
}

bool Enemy::get_finish_attack() {
    return finish_attack;
}

bool Enemy::is_bleeding() {
    return bleeding;
}

f64 Enemy::get_bleed_timer() {
    return bleed_timer;
};

AEVec2 Enemy::get_element_icon_pos() {
    return element_icon_pos;
}

Elements Enemy::get_element() {
    return element_type;
}

std::string Enemy::get_str_damage_number()
{
    return str_damage_number;
}

AEVec2 Enemy::get_str_damage_pos_percent()
{
    return str_damage_pos_percent;
}

bool Enemy::get_bool_damage_num()
{
    return bool_damage_num;
}

float Enemy::get_crit_colour() 
{
    return crit_colour;
}


//Actions
void Enemy::set_position_and_aabb(AEVec2 input_pos) {
    pos.x = input_pos.x;
    pos.y = input_pos.y;
    enemy_aabb = CreateAABB(input_pos, size, size);
    element_icon_pos = {pos.x - 20.0f , pos.y + 60.0f};
    default_str_damage_pos = {pos.x, pos.y + 20.0f};
    str_damage_pos = default_str_damage_pos;
    str_damage_pos_percent = convert_pos(str_damage_pos);
}

int Enemy::elemental_damage_calculator(Elements enemy_type, Elements input_element) 
{
    set_crit_colour(false);
    if (enemy_type == FIRE) 
    {
        if (input_element == POISON) 
        {
            set_crit_colour(true);
            return 1;
        }
        if (input_element == SHADOW)
        {
            return -1;
        }
    }
    if (enemy_type == SHADOW)
    {
        if (input_element == FIRE)
        {
            set_crit_colour(true);
            return 1;
        }
        if (input_element == POISON)
        {
            return -1;
        }
    }

    if (enemy_type == POISON)
    {
        if (input_element == SHADOW)
        {
            set_crit_colour(true);
            return 1;
        }
        if (input_element == FIRE)
        {
            return -1;
        }
    }
    //Reaching here means it is neutral.
    return 0;
}
//When enemy take damage, insert damage number there.
void Enemy::take_damage(int val, Elements input_element)
{
    val += elemental_damage_calculator(element_type,input_element);

    if (alive) { //if alive
        hp -= val;
        if (hp <= 0) {
            hp = 0;
            life_state = dead;
        }
    }

    //storing the damage to text for display.
    str_damage_number = std::to_string(val);
    bool_damage_num = true;
}

void Enemy::set_frame_num(int frame_no){
    frame_num = frame_no;
}

void Enemy::update_animation(f64 dt) {
    frame_timer -= dt;

    if (frame_num == total_frame)
        frame_num = 0;
    
    if (frame_num < 2)
    {
        pos.x -= 5.0f;
        element_icon_pos.x -= 5.0f;
    }
    else
    {
        pos.x+= 5.0f;
        element_icon_pos.x += 5.0f;
    }

    if (frame_timer <= 0) {
        frame_timer = frame_time;
        frame_num++;


        if (frame_num >= total_frame) {
            switch_finish_attack();
            frame_num = total_frame; //Stay at last frame
        }
    }
}

void Enemy::switch_finish_attack() 
{
    finish_attack = !finish_attack;
}

void Enemy::update_bleed_timer() {
    bleed_timer -= g_dt;
}

void Enemy::reset_bleed_time() {
        bleed_timer = bleed_time;  
}

void Enemy::set_bleeding(bool logic) {
    bleeding = logic;
}

AEVec2 Enemy::convert_pos(AEVec2 input_pos) {

    input_pos.x = ((input_pos.x / AEGetWindowWidth()) * 2.0f);
    input_pos.y = ((input_pos.y / AEGetWindowHeight()) * 2.0f);
    
    return input_pos;
}

void Enemy::update_damage_timer()
{
    if (bool_damage_num)
    {
        damage_timer -= (f32)g_dt;
        str_damage_pos.y += 1.0f;
        str_damage_pos_percent = convert_pos(str_damage_pos);

        if (damage_timer < 0.f)
        {
            damage_timer = damage_time; //Resets back to default time.
            str_damage_pos = default_str_damage_pos;
            bool_damage_num = false;
        }
    }
}

void Enemy::set_crit_colour(bool input)
{
    if (input)
    {
        crit_colour = 0.0f;
    }
    else
    {
        crit_colour = 1.0f;
    }
}

//For Audio
bool Enemy::get_audio() 
{
    return audio;
}

void Enemy::set_audio(bool input)
{
    audio = input;
}

//For player damage numbers
void Enemy::set_p_damage_num_pos(AEVec2 const& input)
{
    p_default_damage_num_pos = input;
    p_damage_num_pos = p_default_damage_num_pos;
    p_damage_num_percent_pos = convert_pos(p_damage_num_pos);
}

AEVec2 Enemy::get_p_damage_num_percent_pos()
{
    return p_damage_num_percent_pos;
}

std::string Enemy::get_p_damage_num_str()
{
    return p_damage_num_str;
}

bool Enemy::get_p_bool_damage_num()
{
    return p_bool_damage_num;
}

void Enemy::set_p_bool_damage_num(bool input)
{
    p_bool_damage_num = input;
}

void Enemy::set_p_damage_num_str(std::string input)
{
    p_damage_num_str = input;
}

void Enemy::update_p_damage_timer()
{
    if (p_bool_damage_num)
    {
        p_damage_timer -= (f32)g_dt;
        p_damage_num_pos.y += 2.0f;
        p_damage_num_percent_pos = convert_pos(p_damage_num_pos);
        if (p_damage_timer < 0.f)
        {
            p_damage_timer = p_damage_time; //Resets back to default time.
            p_damage_num_pos = p_default_damage_num_pos;
            p_damage_num_percent_pos = convert_pos(p_damage_num_pos);
            p_bool_damage_num = false;
        }
    }
}

