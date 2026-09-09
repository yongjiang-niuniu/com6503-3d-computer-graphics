#ifndef BEE_HPP
#define BEE_HPP

#include <glm/glm.hpp>
#include <vector>
#include "Shader.hpp"
#include "Sphere.hpp"

class Bee {
public:
    Bee(unsigned int bodyTex, unsigned int wingTex);

    // Update function using deltaTime for smooth movement
    void update(float deltaTime); 

    void draw(Shader& shader, const glm::mat4& view, const glm::mat4& projection);
    
    glm::vec3 getPosition() const { return position; }
    void setPosition(glm::vec3 newPos) { position = newPos; }

private:
    Sphere sphere;
    unsigned int bodyTexture;
    unsigned int wingTexture;

    // State variables
    glm::vec3 position;
    float facingAngle;    // Body orientation
    float wingAngle;      // Wing rotation angle
    float hoverOffset;    // Vertical hover offset

    // Path animation control
    std::vector<glm::vec3> waypoints; // Stores patrol waypoints
    int currentTargetIndex = 0;       // Current target waypoint index
    float moveSpeed = 1.5f;           // Flight speed

    void drawPart(Shader& shader, glm::mat4 parentModel, 
                  glm::vec3 translation, glm::vec3 scale, 
                  glm::vec3 rotationAxis = glm::vec3(0,1,0), float rotationAngle = 0.0f);
};

#endif