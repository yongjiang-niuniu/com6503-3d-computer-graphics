# OpenGL Final Assignment - The Buzzing Scene

This project renders a 3D scene featuring a hierarchical animated character (a Bee) patrolling around three distinct statues. The scene demonstrates dynamic lighting, texture mapping, skybox rendering, and user interaction.

## 🎮 Controls

### Camera & Movement
| Key / Input | Action |
| :--- | :--- |
| **W, A, S, D** | Move the camera (Forward, Left, Back, Right) |
| **Mouse Move** | Look around (Pitch & Yaw) |
| **Scroll** | Zoom in/out (Adjust Field of View) |
| **ESC** | Close the window |

### Lighting Control
| Key | Action |
| :--- | :--- |
| **F** | Toggle **Spotlight** (The moving searchlight) |
| **G** | Toggle **Global Light** (Sunlight) |

### Animation & Modes
| Key | Action |
| :--- | :--- |
| **M** | Toggle **Mode** (Switch between *Continuous Patrol* and *Pose Mode*) |
| **1** | (In Pose Mode) Teleport Bee to **Stone Statue** |
| **2** | (In Pose Mode) Teleport Bee to **Metal Statue** |
| **3** | (In Pose Mode) Teleport Bee to **Wood Statue** |

---

## 🌟 Features Implemented

### 1. Advanced Rendering
* **Skybox:** A dynamic cubemap skybox that slowly rotates to simulate cloud movement.
* **Textures:** Utilizes diffuse maps for the bee, ground, and statues.
* **Statues:** Three distinct material types (Stone, Metal, Wood).

### 2. Hierarchical Modeling (The Bee)
* **Scene Graph:** The Bee is constructed using a hierarchical model (Body -> Head, Wings, Tail, Antennae).
* **Animation:**
    * **Wings:** Flapping animation using sine waves.
    * **Hovering:** Vertical floating motion (Visual offset only, prevents clipping).
    * **Orientation:** The bee automatically faces its flight direction using `atan2`.

### 3. Lighting System
* **Global Light:** Directional sunlight source (Toggleable with 'G').
* **Spotlight:** A dynamic spotlight that rotates around the scene in a circular path.
* **Light Source Rendering:** The spotlight's physical position is rendered as a glowing sphere (Light Bulb) to visualize the scene graph node.

### 4. Logic & Pathfinding
* **Patrol Path:** The bee follows a predefined set of 5 waypoints (looping) around the statues.
* **Smooth Movement:** Interpolated movement based on `deltaTime` for frame-rate independence.
* **Pose Mode:** A debug/pose mode allowing the user to manually place the bee at specific interaction points.

---

## 📂 File Structure

* `main.cpp`: Entry point. Handles window setup, input processing (WASD/Keys), and the main render loop.
* `Bee.cpp / .hpp`: The Bee class. Handles hierarchical drawing, path update logic, and wing animations.
* `Statue.hpp`: Encapsulates statue rendering and texture management.
* `Skybox.hpp`: Handles loading and rendering the cubemap.
* `Ground.hpp`: Renders the floor plane.
* `Sphere.hpp`: Helper class to generate and draw sphere geometry (used for Bee parts and Light Bulb).
* `Shader.hpp`: GLSL shader program wrapper.
* `stb_image.h`: Image loading library.

---

## 🛠️ Dependencies & Build

This project requires a C++ compiler and the following OpenGL libraries:

* **GLFW** (Windowing and Input)
* **GLAD** (OpenGL Function Pointer Loader)
* **GLM** (OpenGL Mathematics)
* **STB Image** (Texture loading - included in source)

### CMake Build
The project has been successfully compiled. 
You can run the My3DGraphicsProject.exe located in the build folder to view the full content. 
If you wish to recompile, please execute the following command string within the build directory:

cd ..
rm -r build
mkdir build
cd build
cmake -G "Ninja" ..
cmake --build .