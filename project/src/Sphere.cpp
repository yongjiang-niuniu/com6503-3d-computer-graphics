#include "Sphere.hpp"
#include <cmath>
#include <iostream>

Sphere::Sphere(float radius, unsigned int stacks, unsigned int slices) {
    std::cout << "DEBUG: [Sphere] Constructor started..." << std::endl; // <--- 加这行
    buildMesh(radius, stacks, slices);
    std::cout << "DEBUG: [Sphere] Constructor finished!" << std::endl;  // <--- 加这行
}

void Sphere::buildMesh(float radius, unsigned int stacks, unsigned int slices) {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i <= stacks; ++i) {
        float v = 1.0f - (float)i / stacks;
        float phi = v * 3.1415926535f;   // ★ 替换 glm::pi<float>()

        for (unsigned int j = 0; j <= slices; ++j) {
            float u = (float)j / slices;
            float theta = u * 6.283185307f;   // ★ 替换 glm::two_pi<float>()

            float x = sin(phi) * cos(theta);
            float y = cos(phi);
            float z = sin(phi) * sin(theta);

            vertices.push_back(radius * x);
            vertices.push_back(radius * y);
            vertices.push_back(radius * z);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            vertices.push_back(u);
            vertices.push_back(v);
        }
    }

    for (unsigned int i = 0; i < stacks; ++i) {
        for (unsigned int j = 0; j < slices; ++j) {
            unsigned int a = i * (slices + 1) + j;
            unsigned int b = a + slices + 1;

            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(a + 1);

            indices.push_back(b);
            indices.push_back(b + 1);
            indices.push_back(a + 1);
        }
    }

    indexCount = indices.size();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    int stride = 8 * sizeof(float);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Sphere::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
