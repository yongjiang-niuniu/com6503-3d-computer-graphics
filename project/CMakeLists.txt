cmake_minimum_required(VERSION 3.10)
project(My3DGraphicsProject)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(My3DGraphicsProject
    src/main.cpp
    src/Shader.cpp
    src/Skybox.cpp
    src/Sphere.cpp
    src/Statue.cpp
    src/Ground.cpp
    src/glad.c
    src/Bee.cpp
    src/stb_setup.cpp
)

target_link_libraries(My3DGraphicsProject
    glfw3
    opengl32
)
