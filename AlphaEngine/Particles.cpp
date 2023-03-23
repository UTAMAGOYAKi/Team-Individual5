#include "Particles.h"

//This function creates one particle in that frame. Use it somewhere where it can be called over a period of time.
void create_particle(std::vector<particle>& particle_vector, size_t particle_max, AEVec2 starting_pos, particle (*callback)(AEVec2 pos)) {

    if (particle_vector.size() < particle_max)
    {
        particle new_particle = callback(starting_pos);
        particle_vector.push_back(new_particle);
    }
}

//Put in under //Particle Update.
void update_particle(std::vector<particle>& particle_vector)
{
    for (int i = 0; i < particle_vector.size(); i++)
    {
        if (particle_vector[i].lifespan < 0)
        {
            particle_vector.erase(particle_vector.begin() + i);
        }
        else
        {
            particle_vector[i].lifespan -= g_dt;
            particle_vector[i].position.x += particle_vector[i].velocity.x;
            particle_vector[i].position.y += particle_vector[i].velocity.y;
        }
    }
}

//Put in under //Particles Drawing in GameState.
void draw_particles(std::vector<particle> particle_vector, AEGfxVertexList* particle_mesh, AEGfxTexture* particle_texture) {

    AEMtx33 scale2, trans, matrix;

    for (int i = 0; i < particle_vector.size(); ++i)
    {
        AEGfxTextureSet(particle_texture, 0, 0);
        //Apply scale
        AEMtx33Scale(&scale2, particle_vector[i].size, particle_vector[i].size);
        //Apply translation
        AEMtx33Trans(&trans, particle_vector[i].position.x, particle_vector[i].position.y);
        //Concatenate the scale and translation matrix
        AEMtx33Concat(&matrix, &trans, &scale2);
        //Concatenate the result with the particle's matrix
        //Send the resultant matrix to the graphics manager using "AEGfxSetTransform"
        AEGfxSetTransform(matrix.m);
        //Draw the particle's mesh
        AEGfxMeshDraw(particle_mesh, AE_GFX_MDM_TRIANGLES);
    }
}

//DEFINATIONS OF PARTICLE BEHAVIORS
//Return particle object with a pos
particle enemy_take_damage_particle(AEVec2 pos)
{
    particle new_particle;
    //Contiune
    new_particle.size = fmodf((float)rand(), 10.0f) + 8.0f;
    new_particle.lifespan = fmodf((float)rand(), .3f) + 0.2f;
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
    return new_particle;
}