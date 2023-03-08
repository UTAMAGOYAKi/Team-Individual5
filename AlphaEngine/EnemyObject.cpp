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

//Actions
void Enemy::set_position_and_aabb(AEVec2 input_pos) {
    pos.x = input_pos.x;
    pos.y = input_pos.y;
    enemy_aabb = CreateAABB(input_pos, size, size);
}

//When enemy take damage, insert damage number there.
void Enemy::take_damage(int val) {
    if (alive) { //if alive
        hp -= val;
        if (hp <= 0) {
            hp = 0;
            life_state = dead;
        }
    }
}


void Enemy::set_frame_num(int frame_no){
    frame_num = frame_no;
}

void Enemy::update_animation(f64 dt) {
    frame_timer -= dt;

    if (frame_timer <= 0) {
        frame_timer = frame_time;
        frame_num++;

        if (frame_num > 2) {
            frame_num = 2;
        }
    }
}
