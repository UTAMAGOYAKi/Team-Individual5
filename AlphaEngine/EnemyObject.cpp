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

    if (frame_num == total_frame)
        frame_num = 0;

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

void Enemy::create_particle(std::vector<particle>& particle_vector, int particle_max) {

    if (particle_vector.size() < particle_max)
    {
        
        particle new_particle;
        //Contiune
        new_particle.size = fmodf((float)rand(), 50.0f) + 30.0f;
        new_particle.lifespan = fmodf((float)rand(), .3f) +0.2f;
        new_particle.position = pos;

        AEVec2 new_vel;
        //int num = rand();
        if (rand() % 2) {
            AEVec2Set(&new_vel, fmodf((float)rand(), 5.0f), fmodf((float)rand(), 5.0f));
        }
        else
        {
            AEVec2Set(&new_vel, -fmodf((float)rand(), 5.0f), fmodf((float)rand(), 5.0f));
        }

        new_particle.velocity = new_vel;
        particle_vector.push_back(new_particle);
    }
}

//NOT USED;
void update_particle(std::vector<particle> particle_vector)
{
    for (int i = 0; i < particle_vector.size(); i++)
    {
        if (particle_vector[i].lifespan < 0)
        {
            particle_vector.erase(particle_vector.begin() + i);
        }
        else
        {
            particle_vector[i].lifespan -= AEFrameRateControllerGetFrameTime();
            particle_vector[i].position.x += particle_vector[i].velocity.x;
            particle_vector[i].position.y += particle_vector[i].velocity.y;
        }
    }
}

void Enemy::update_bleed_timer() {
    bleed_timer -= AEFrameRateControllerGetFrameTime();
}

void Enemy::reset_bleed_time() {
        bleed_timer = bleed_time;  
}

void Enemy::set_bleeding(bool logic) {
    bleeding = logic;
}

//Bleeding

