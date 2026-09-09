#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.hpp"

class Skybox {
public:
    // directory like "../assets/bkg/lightblue"
    Skybox(const std::string& directory);

    void draw(const glm::mat4& view, const glm::mat4& projection);

private:
    unsigned int VAO = 0, VBO = 0;
    unsigned int cubemapTex = 0;
    Shader shader; 

    unsigned int loadCubemap(const std::string& directory);
    void initCube();
};

#endif
