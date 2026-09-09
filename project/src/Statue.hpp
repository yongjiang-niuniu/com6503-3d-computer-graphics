#ifndef STATUE_HPP
#define STATUE_HPP

#include <glm/glm.hpp>
#include <string>
#include "Sphere.hpp"
#include "Shader.hpp"

class Statue {
public:
    // 构造函数：接收 普通脸、惊恐脸、高光贴图、位置、身材缩放
    Statue(const std::string& normalPath,
           const std::string& scaredPath,
           const std::string& specularPath,
           glm::vec3 position,
           glm::vec3 scale);

    // 绘制函数：新增 beePos 参数，用于计算距离
    void draw(Shader& shader, const glm::mat4& view, const glm::mat4& projection, glm::vec3 beePos);

private:
    Sphere sphere;
    unsigned int normalTex;  // 普通表情
    unsigned int scaredTex;  // 惊恐表情
    unsigned int specularTex;
    
    glm::vec3 pos;
    glm::vec3 scaleFactors;

    unsigned int loadTexture(const char* path);
};

#endif