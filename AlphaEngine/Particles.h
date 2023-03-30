/******************************************************************************/
/*!
\file		Particles.h
\author 	Yeo Jun Jie
\par    	email: yeo.junjie\@digipen.edu
\brief		Functions to help create particles effects in the game.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#pragma once

#include "Main.h"
#include "string"
#include "vector"
#include <AEVec2.h>

//Particle object
struct particle
{
    AEVec2 position;
    AEVec2 velocity;
    f64 lifespan;
    float size;
};

//particle object that contains the vector of particles and the max capacity of particles that should be created.
struct particle_manager {
    std::vector<particle> particle_vector{};
    size_t max_capacity{};

    //Single argument constructor, max_cap is the number of particles that can be drawn by this manager.
    //Please declare in the global first.
    particle_manager(size_t max_cap): max_capacity{max_cap}{}
};

//Non-Member Functions:

//Read more details in particles.h on where to put them.
void create_particle(std::vector<particle>& particle_vector, size_t particle_max, AEVec2 pos, particle (*callback)(AEVec2 pos));
void update_particle(std::vector<particle>& particle_vector);
void draw_particles(std::vector<particle> particle_vector, AEGfxVertexList* particle_mesh, AEGfxTexture* particle_texture);

//Functions that creates the behaviour of the particles (to be used for create particle)
particle enemy_take_damage_particle(AEVec2 pos);
