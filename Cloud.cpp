#include "Cloud.h"
#include <glm\gtc\type_ptr.hpp>


Cloud::Cloud() {
  
    std::vector<glm::vec3> vertices
    {
        glm::vec3(-899, 899, 899),
        glm::vec3(-899, -899, 899),
        glm::vec3(899, -899, 899),
        glm::vec3(899, 899, 899),
        glm::vec3(-899, 899, -899),
        glm::vec3(-899, -899, -899),
        glm::vec3(899, -899, -899),
        glm::vec3(899, 899, -899)
    };

    for (glm::vec3 v : vertices) {
        v = v * 50.0f;
    }

    std::vector<glm::ivec3> indices
    {
        // REVERSE FACES
       // Front face.
       glm::ivec3(0, 2, 1),
       glm::ivec3(2, 0, 3),
       // Back face.
       glm::ivec3(7, 5, 6),
       glm::ivec3(5, 7, 4),
       // Right face.
       glm::ivec3(3, 6, 2),
       glm::ivec3(6, 3, 7),
       // Left face.
       glm::ivec3(4, 1, 5),
       glm::ivec3(1, 4, 0),
       // Top face.
       glm::ivec3(4, 3, 0),
       glm::ivec3(3, 4, 7),
       // Bottom face.
       glm::ivec3(1, 6, 5),
       glm::ivec3(6, 1, 2)
    };

    // Generate a vertex array (VAO) and two vertex buffer objects (VBO).
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Bind to the VAO.
    glBindVertexArray(vao);
    
    // Bind to the first VBO. We will use it to store the vertices.
    glGenBuffers(2, vbos);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    // Pass in the data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(),
        vertices.data(), GL_STATIC_DRAW);
    // Enable vertex attribute 0. 
    // We will be able to access vertices through it.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    // Bind to the second VBO. We will use it to store the indices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]);
    // Pass in the data.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * indices.size(),
        indices.data(), GL_STATIC_DRAW);

    // Unbind from the VBOs. 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);

}

Cloud::~Cloud() {
    glDeleteBuffers(2, vbos);
    glDeleteVertexArrays(1, &vao);
}

void Cloud::draw() {

    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE);
    glBindVertexArray(vao);
    // elemnt array buffer.
    if (!pityPoints)

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); 
    else {
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
    glBindVertexArray(0);
    glEnable(GL_TEXTURE);
}

void Cloud::setPityPoints(bool p) {
    pityPoints = p;
}

void Cloud::update() {
	
}