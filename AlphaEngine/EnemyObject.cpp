#include "EnemyObject.h"
#include "Buttons.h"

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
    return alive;
}

//Actions
void Enemy::set_position(AEVec2 input_pos) {
    pos.x = input_pos.x;
    pos.y = input_pos.y;
    enemy_aabb = CreateAABB(input_pos, size, size);
    //std::cout << enemy_aabb.mid.x << " " << enemy_aabb.mid.y << std::endl;
}

//for getting healed or damage
void Enemy::take_damage(int val) {
    if (alive) { //if alive
        hp -= val;
        if (hp <= 0) {
            hp = 0;
            alive = false;
        }
    }
}