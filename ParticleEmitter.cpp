#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(int num_particles) {

     GLfloat particle_quad[] = {
     0.0f, 1.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
     0.0f, 0.0f, 0.0f,

     0.0f, 1.0f, 0.0f,
     1.0f, 1.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
     };

     //GLfloat particle_tex[] = {
     //    0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
     //};

     // generate vertex array
     glGenVertexArrays(1, &vao);
     glBindVertexArray(vao);

     // generate buffer
     glGenBuffers(2, vbo);
     glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
     glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
     glBindVertexArray(0);

     /*
     glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
     glBufferData(GL_ARRAY_BUFFER, sizeof(particle_tex), particle_tex, GL_STATIC_DRAW);
     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
     glBindVertexArray(1);*/

     // generate texture
     glGenTextures(1, &textureID);
     glBindTexture(GL_TEXTURE_2D, textureID);

     int width, height, comp;

     unsigned char* data = stbi_load("images/particle.png", &width, &height, &comp, 0);
     if (data)
     {
         std::cout << "Successfully loaded texture." << std::endl;
         if (comp == 3)
             glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
         else if (comp == 4)
             glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
         stbi_image_free(data);
     }
     else
     {
         std::cout << "Cubemap texture failed to load at path: " << "images/particle.png" << std::endl;
         stbi_image_free(data);
     }

     this->numParticles = num_particles;
     for (unsigned i = 0; i < num_particles; i++) {
         particles.push_back(Particle());
     }
}

ParticleEmitter::~ParticleEmitter() {
    glDeleteBuffers(2, vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1, &textureID);
}

int ParticleEmitter::firstUnusedParticle()
{
    for (GLuint i = lastUsedParticle; i < numParticles; ++i) {
        if (particles[i].life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    for (GLuint i = 0; i < lastUsedParticle; ++i) {
        if (particles[i].life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }
    lastUsedParticle = 0;
    return 0;
}

void ParticleEmitter::respawnParticle(Particle& particle, glm::vec3 pos, glm::vec3 offset)
{
    GLfloat random = ((rand() % 100) - 50) / 10.0f;
    GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
    particle.position = glm::vec3(pos) + random + offset;
    particle.color = glm::vec4(rColor, rColor, rColor, 1.0f);
    particle.life = 1.0f;
    particle.velocity = pos * 0.1f;
}

void ParticleEmitter::draw() {
    {

        glEnable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        for (auto p : particles)
        {
            if (p.life > 0.0f)
            {
                glBindTexture(GL_TEXTURE_2D, textureID);
                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);// , particles.size());
                glBindVertexArray(0);
            }
        }
        // Don't forget to reset to default blending mode
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}

void ParticleEmitter::update() 
{
    update(glm::vec3(0, 0, 0));
}

void ParticleEmitter::update(glm::vec3 pos)
{
    // add more particles to the emitter
    GLuint nr_new_particles = 2;
    for (GLuint i = 0; i < nr_new_particles; ++i)
    {
        int unusedParticle = firstUnusedParticle();
        respawnParticle(particles[unusedParticle], pos, glm::vec3(0, 0, 0));
    }

    // Uupdate all particles
    for (GLuint i = 0; i < numParticles; ++i)
    {
        Particle& p = particles[i];
        p.life -= dt;
        if (p.life > 0.0f)
        {	// particle is alive, thus update
            p.position -= p.velocity * dt;
            // reduce opacity of particle
            p.color.a -= dt * 2.5;
        }
    }
}