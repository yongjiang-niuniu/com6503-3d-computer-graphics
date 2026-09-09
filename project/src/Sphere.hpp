#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Sphere {
public:
    Sphere(float radius = 1.0f, unsigned int stacks = 32, unsigned int slices = 32);
    void draw();

private:
    unsigned int VAO, VBO, EBO;
    unsigned int indexCount;

    void buildMesh(float radius, unsigned int stacks, unsigned int slices);
};

#endif
