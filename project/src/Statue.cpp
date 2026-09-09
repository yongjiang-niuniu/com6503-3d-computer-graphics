#include "Statue.hpp"
#include <glad/glad.h>
#include <iostream>
#include "stb_image.h"
#include <glm/gtc/matrix_transform.hpp>

Statue::Statue(const std::string& normalPath,
               const std::string& scaredPath,
               const std::string& specularPath,
               glm::vec3 position,
               glm::vec3 scale)
: sphere(1.0f), pos(position), scaleFactors(scale)
{
    // 1. 先尝试加载所有图片
    std::cout << "DEBUG: Loading textures for statue at " << position.x << "..." << std::endl;
    
    normalTex = loadTexture(normalPath.c_str());
    scaredTex = loadTexture(scaredPath.c_str());
    specularTex = loadTexture(specularPath.c_str());

    // 2. ⭐⭐⭐ 超级防崩逻辑 ⭐⭐⭐
    
    // 如果高光图挂了，就随便给个非0的值（如果有）或者保持0
    // 关键是看 diffuse (normalTex)
    
    // 如果普通脸加载失败...
    if (normalTex == 0) {
        std::cout << "❌ CRITICAL WARNING: Failed to load " << normalPath << std::endl;
        
        // 救命稻草：如果高光图活着，就用高光图顶替
        if (specularTex != 0) {
            std::cout << " -> Fallback to specular texture." << std::endl;
            normalTex = specularTex; 
        } else {
            // 如果连高光图都没了，说明路径全错了。
            // 此时我们保持为 0，但在 draw 里会处理
            std::cout << " -> No fallback available. Statue may be black." << std::endl;
        }
    }

    // 如果惊恐脸加载失败，就用普通脸
    if (scaredTex == 0) {
        scaredTex = normalTex;
    }
}

void Statue::draw(Shader& shader, const glm::mat4& view, const glm::mat4& projection, glm::vec3 beePos)
{
    // ⭐ 防崩检查：如果连纹理都没有，为了防止闪退，直接不画这个石像了
    // 或者只画黑色的
    if (normalTex == 0 && specularTex == 0) {
        return; 
    }

    shader.use();

    // 距离检测
    float distance = glm::length(pos - beePos);
    float safeDistance = 4.0f; 

    // 绑定纹理
    glActiveTexture(GL_TEXTURE0);
    
    // 确保我们不绑定 0 (0 会导致闪退)
    unsigned int targetTex = (distance < safeDistance) ? scaredTex : normalTex;
    if (targetTex == 0) targetTex = specularTex; // 最后的救命稻草
    
    if (targetTex != 0) {
        glBindTexture(GL_TEXTURE_2D, targetTex);
    }

    glActiveTexture(GL_TEXTURE1);
    if (specularTex != 0) {
        glBindTexture(GL_TEXTURE_2D, specularTex);
    }

    // 设置矩阵
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, scaleFactors); 

    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    
    shader.setInt("diffuseMap", 0);
    shader.setInt("specularMap", 1);

    sphere.draw();
}

unsigned int Statue::loadTexture(const char* path)
{
    unsigned int textureID = 0; // 默认为 0
    int width, height, nrComponents;
    
    // 打印路径，帮你看看到底是哪个文件找不到
    std::cout << "   Trying: " << path << " ... ";
    
    stbi_set_flip_vertically_on_load(false);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

    if (data)
    {
        glGenTextures(1, &textureID);
        GLenum format = (nrComponents == 3 ? GL_RGB : GL_RGBA);

        glBindTexture(GL_TEXTURE_2D, textureID);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
        
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        std::cout << "OK!" << std::endl;
    }
    else
    {
        std::cout << "FAILED! (File not found)" << std::endl;
        // 不要 stbi_image_free(data) 因为 data 是 NULL
    }

    return textureID;
}