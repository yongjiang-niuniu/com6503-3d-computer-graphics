#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Statue.hpp"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "Ground.hpp"
#include "Bee.hpp" 
#include "Sphere.hpp" // Required to draw the spotlight source entity
#include "stb_image.h" 

// --- Function Declarations ---
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char* path);

// --- Global Variables ---
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Camera settings
glm::vec3 cameraPos   = glm::vec3(0.0f, 5.0f, 15.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, -0.2f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw   = -90.0f; 
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0f / 2.0;
float fov   =  45.0f;

float deltaTime = 0.0f; 
float lastFrame = 0.0f;

// --- State Control ---
bool spotLightOn = true;
bool worldLightOn = true;
bool spotLightKeyPressed = false; 
bool worldLightKeyPressed = false;

// Pose Mode State
bool isPoseMode = false;
bool modeKeyPressed = false;

// Global pointer to Bee for access within processInput
Bee* globalBeePtr = nullptr; 

int main() {
    // 1. Initialize GLFW
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Final Assignment - Buzz", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;
    glEnable(GL_DEPTH_TEST);

    // 2. Resource Preparation
    Shader basicShader("../shaders/basic.vert", "../shaders/basic.frag");
    Skybox skybox("../assets/bkg/lightblue");
    Ground ground;
    
    // Spotlight physical model (a small sphere)
    Sphere lightBulb(0.5f, 24, 24); 

    std::cout << "DEBUG: Loading Statues..." << std::endl;
    // Initialize Statues
    Statue stoneStatue(
        "../assets/textures/statue/stone/stone_face_normal.jpg",
        "../assets/textures/statue/stone/stone_face_scared.jpg",
        "../assets/textures/statue/stone/stone_face_normal.jpg", 
        glm::vec3(-3.0f, 1.0f, 0.0f), glm::vec3(1.2f, 2.5f, 1.2f)
    );
    Statue metalStatue(
        "../assets/textures/statue/metal/metal_face_normal.jpg",
        "../assets/textures/statue/metal/metal_face_scared.jpg",
        "../assets/textures/statue/metal/metal_face_normal.jpg",
        glm::vec3(3.0f, 1.75f, 0.0f), glm::vec3(0.6f, 3.5f, 0.6f)
    );
    Statue woodStatue(
        "../assets/textures/statue/wood/wood_face_normal.jpg",
        "../assets/textures/statue/wood/wood_face_scared.jpg",
        "../assets/textures/statue/wood/wood_face_normal.jpg",
        glm::vec3(0.0f, 0.75f, -4.0f), glm::vec3(1.6f, 1.5f, 1.6f)
    );

    // Initialize Bee
    unsigned int beeBodyTex = loadTexture("../assets/textures/statue/wood/diffuse.jpg");
    unsigned int beeWingTex = loadTexture("../assets/textures/statue/metal/diffuse.jpg");
    Bee bee(beeBodyTex, beeWingTex);
    globalBeePtr = &bee; // Link global pointer

    // 3. Render Loop
    while (!glfwWindowShouldClose(window)) {
        basicShader.setBool("isLightSource", false);
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        basicShader.use();

        // Camera setup
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        
        // --- Lighting Setup ---
        // 1. Directional Sun Light
        basicShader.setVec3("lightPos", glm::vec3(5.0f, 10.0f, 5.0f));
        basicShader.setVec3("lightColor", glm::vec3(0.9f, 0.9f, 0.9f));
        basicShader.setBool("lightOn", worldLightOn); 
        
        // 2. Spotlight (Fixed position, rotating direction)
        glm::vec3 spotPos = glm::vec3(0.0f, 8.0f, 0.0f); 
        float spotX = sin(currentFrame * 1.5f) * 4.0f;
        float spotZ = cos(currentFrame * 1.5f) * 4.0f;
        glm::vec3 targetPos = glm::vec3(spotX, 0.0f, spotZ); 
        glm::vec3 spotDir = normalize(targetPos - spotPos);

        basicShader.setVec3("spotPos", spotPos);
        basicShader.setVec3("spotDir", spotDir);
        basicShader.setFloat("spotCutOff", glm::cos(glm::radians(15.0f))); 
        basicShader.setBool("spotOn", spotLightOn);
        basicShader.setVec3("viewPos", cameraPos);


        if (!isPoseMode) {
            // Update bee with deltaTime for smooth movement
            bee.update(deltaTime); 
        } else {
            // Update bee (delta passed to keep animation running, but position is overridden by inputs)
            bee.update(deltaTime);
        }
        glm::vec3 beePos = bee.getPosition();

        // --- Draw Objects ---
        ground.draw(basicShader, view, projection);
        stoneStatue.draw(basicShader, view, projection, beePos);
        metalStatue.draw(basicShader, view, projection, beePos);
        woodStatue.draw(basicShader, view, projection, beePos);
        bee.draw(basicShader, view, projection);

        // --- Draw Spotlight Entity ---
        // Render a small sphere at the spotlight's origin to visualize the scene graph node
        if (spotLightOn) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, spotPos);
            model = glm::scale(model, glm::vec3(0.2f)); // Scale down to look like a bulb
            basicShader.setMat4("model", model);
            
            // Enable emission mode for the bulb
            basicShader.setBool("isLightSource", true); 
            
            lightBulb.draw();
            
            // Disable emission mode immediately after drawing
            basicShader.setBool("isLightSource", false); 
        }
        // --- Draw Skybox ---
        // Rotate the view matrix slowly to simulate cloud movement
        glm::mat4 skyView = glm::rotate(view, (float)glfwGetTime() * 0.05f, glm::vec3(0.0f, 1.0f, 0.0f));
        skybox.draw(skyView, projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// --- Input Processing ---
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // WASD Movement
    float velocity = 5.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cameraPos += cameraFront * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cameraPos -= cameraFront * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * velocity;

    // Light Toggles (F: Spotlight, G: Global Light)
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        if (!spotLightKeyPressed) { spotLightOn = !spotLightOn; spotLightKeyPressed = true; }
    } else spotLightKeyPressed = false;

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        if (!worldLightKeyPressed) { worldLightOn = !worldLightOn; worldLightKeyPressed = true; }
    } else worldLightKeyPressed = false;

    // Mode Toggle (M: Switch Pose/Continuous)
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        if (!modeKeyPressed) {
            isPoseMode = !isPoseMode;
            modeKeyPressed = true;
            std::cout << "Mode: " << (isPoseMode ? "POSE (Use 1,2,3)" : "CONTINUOUS") << std::endl;
        }
    } else modeKeyPressed = false;

    // Position Control in Pose Mode
    if (isPoseMode && globalBeePtr) {
        // Move to Stone Statue
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) 
            globalBeePtr->setPosition(glm::vec3(-3.0f, 1.0f, 2.5f)); 
        // Move to Metal Statue
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) 
            globalBeePtr->setPosition(glm::vec3(3.0f, 1.75f, 2.5f));
        // Move to Wood Statue
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) 
            globalBeePtr->setPosition(glm::vec3(0.0f, 0.75f, -2.0f));
    }
}

// Mouse Callback
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse) { lastX = xpos; lastY = ypos; firstMouse = false; }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos; lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f) fov = 1.0f;
    if (fov > 45.0f) fov = 45.0f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Texture Loader Utility
unsigned int loadTexture(const char* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(false); 
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format = (nrComponents == 3) ? GL_RGB : GL_RGBA;
        glBindTexture(GL_TEXTURE_2D, textureID);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load: " << path << std::endl;
        stbi_image_free(data);
        return 0;
    }
    return textureID;
}