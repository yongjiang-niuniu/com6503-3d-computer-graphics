#include "Bee.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <iostream>

// Required for GLFW time functions
#include <GLFW/glfw3.h> 

Bee::Bee(unsigned int bodyTex, unsigned int wingTex) 
    : bodyTexture(bodyTex), wingTexture(wingTex) 
{
    position = glm::vec3(0.0f, 3.0f, 0.0f);
    sphere = Sphere(1.0f, 24, 24);

    // Initialize 5 patrol waypoints
    // Waypoints include statue locations (to trigger reactions) and aerial points
    waypoints.push_back(glm::vec3(-3.0f, 2.0f, 2.5f));  // In front of Statue 1
    waypoints.push_back(glm::vec3(0.0f, 4.0f, 0.0f));   // Aerial transition point A
    waypoints.push_back(glm::vec3(3.0f, 2.5f, 2.5f));   // In front of Statue 2
    waypoints.push_back(glm::vec3(0.0f, 5.0f, -6.0f));  // Aerial transition point B
    waypoints.push_back(glm::vec3(0.0f, 2.0f, -2.0f));  // In front of Statue 3 (Raised to prevent clipping)
    
    currentTargetIndex = 0;
    facingAngle = 0.0f;
}

void Bee::update(float deltaTime) {
    // 1. Wing animation (based on total time)
    float time = (float)glfwGetTime();
    wingAngle = sin(time * 25.0f) * 45.0f; 
    
    // Hover effect: sinusoidal vertical offset
    hoverOffset = sin(time * 3.0f) * 0.2f; 

    // 2. Patrol logic
    if (waypoints.empty()) return;

    // Get current target
    glm::vec3 target = waypoints[currentTargetIndex];

    // Calculate direction vector
    glm::vec3 direction = target - position;
    float distance = glm::length(direction);

    // Check if reached the waypoint
    if (distance < 0.1f) {
        currentTargetIndex++;
        // Loop back to the first waypoint
        if (currentTargetIndex >= waypoints.size()) {
            currentTargetIndex = 0;
        }
    } 
    else {
        // Move towards target
        glm::vec3 moveStep = glm::normalize(direction) * moveSpeed * deltaTime;
        position += moveStep;

        // Update orientation to face movement direction
        if (glm::length(moveStep) > 0.001f) {
             facingAngle = atan2(direction.x, direction.z);
        }
    }
}

void Bee::draw(Shader& shader, const glm::mat4& view, const glm::mat4& projection) {
    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    
    // 1. Body (Root Node)
    glm::mat4 bodyModel = glm::mat4(1.0f);

    // Apply hover offset to visual position only (does not affect logic position)
    glm::vec3 visualPosition = position;
    visualPosition.y += hoverOffset; 

    bodyModel = glm::translate(bodyModel, visualPosition);
    bodyModel = glm::rotate(bodyModel, facingAngle, glm::vec3(0.0f, 1.0f, 0.0f));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bodyTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, bodyTexture);

    drawPart(shader, bodyModel, glm::vec3(0,0,0), glm::vec3(0.5f, 0.5f, 0.7f));

    // 2. Head
    drawPart(shader, bodyModel, glm::vec3(0.0f, 0.1f, 0.5f), glm::vec3(0.35f));

    // Eyes
    drawPart(shader, bodyModel, glm::vec3(0.15f, 0.3f, 0.7f), glm::vec3(0.1f));
    drawPart(shader, bodyModel, glm::vec3(-0.15f, 0.3f, 0.7f), glm::vec3(0.1f));

    // Antennae
    drawPart(shader, bodyModel, glm::vec3(0.15f, 0.5f, 0.6f), glm::vec3(0.05f));
    drawPart(shader, bodyModel, glm::vec3(0.2f, 0.6f, 0.65f), glm::vec3(0.04f));
    drawPart(shader, bodyModel, glm::vec3(-0.15f, 0.5f, 0.6f), glm::vec3(0.05f));
    drawPart(shader, bodyModel, glm::vec3(-0.2f, 0.6f, 0.65f), glm::vec3(0.04f));

    // 3. Tail
    drawPart(shader, bodyModel, glm::vec3(0.0f, -0.1f, -0.6f), glm::vec3(0.3f, 0.3f, 0.5f));

    // 4. Wings
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, wingTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, wingTexture);

    // Left Wing
    drawPart(shader, bodyModel, glm::vec3(0.2f, 0.4f, 0.1f), glm::vec3(0.6f, 0.02f, 0.3f), glm::vec3(0,0,1), -wingAngle);
    // Right Wing
    drawPart(shader, bodyModel, glm::vec3(-0.2f, 0.4f, 0.1f), glm::vec3(0.6f, 0.02f, 0.3f), glm::vec3(0,0,1), wingAngle);
}

void Bee::drawPart(Shader& shader, glm::mat4 parentModel, 
                  glm::vec3 translation, glm::vec3 scale, 
                  glm::vec3 rotationAxis, float rotationAngle) 
{
    glm::mat4 model = glm::translate(parentModel, translation);
    if (abs(rotationAngle) > 0.001f) {
        model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis);
    }
    model = glm::scale(model, scale);
    shader.setMat4("model", model);
    sphere.draw();
}