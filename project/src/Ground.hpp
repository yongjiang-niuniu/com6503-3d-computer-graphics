#ifndef GROUND_HPP
#define GROUND_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.hpp"

class Ground {
public:
    Ground();
    
    // Render the ground plane
    void draw(Shader& shader, const glm::mat4& view, const glm::mat4& projection);

private:
    unsigned int VAO, VBO, EBO;
    unsigned int diffuseTexture, specularTexture;

    // Initialize mesh data (buffers and attributes)
    void setupMesh();

    // Helper function to load texture images
    unsigned int loadTexture(const char* path);
};

#endif