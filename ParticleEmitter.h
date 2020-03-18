#ifndef _PARTICLEEMITTER_H_
#define _PARTICLEEMITTER_H_

#include <glm\fwd.hpp>
#include <GL\glew.h>
#include "Object.h"
#include "stb_image.h"
#include <iostream>


// Structure for each particle
struct Particle {
    glm::vec3 position, velocity;
    glm::vec4 color;
    GLfloat life = 1.0f;

    Particle()
        : position(0.0f), velocity(0.0f), color(1.0f), life(1.0f) { }
};

class ParticleEmitter : public Object {

private:

    GLuint vao, vbo[2];
    GLuint textureID;

    float dt = 0.05;
    int numParticles;
    int lastUsedParticle = 0;
    std::vector<Particle> particles;

public:

    // Instantiate particle emitter with number of particles
    ParticleEmitter::ParticleEmitter(int num_particles);

    int ParticleEmitter::firstUnusedParticle();

    void ParticleEmitter::respawnParticle(Particle& particle, glm::vec3 pos, glm::vec3 offset);

    void ParticleEmitter::draw();
    
    // unused version of update
    void ParticleEmitter::update();

    // our update
    void ParticleEmitter::update(glm::vec3 pos);
};

#endif