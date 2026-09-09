# Build and run the submitted scene

## Original target

The [CMake project](../project/CMakeLists.txt) requests C++17 and CMake 3.10 or newer. It compiles eight C++ translation units and the generated GLAD C loader, then links `glfw3` and Windows `opengl32`.

The original ZIP's CMake cache records a Windows MinGW compiler, Ninja and CMake 4.2.0. The included GLFW DLL and libraries are Windows x64 artifacts. The scene requests an OpenGL 3.3 core context and uses GLSL 330 shaders.

Required for the original build:

- A compatible Windows x64 MinGW C/C++ toolchain.
- CMake and Ninja available to the build environment.
- An OpenGL driver supporting the requested 3.3 core context.
- The bundled headers and libraries in `project/include/` and `project/lib/`, plus the original `assets/` and `shaders/` directories.

The library versions identified from included headers are GLFW 3.4, GLM 1.0.2, GLAD 0.1.36 and stb_image 2.30. The GLFW binary build's exact toolchain was not independently established.

## Clean Windows build

From the repository root, in a terminal configured for the MinGW toolchain:

```bat
cmake -S project -B project/build-recovered -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build project/build-recovered
cd project\build-recovered
.\My3DGraphicsProject.exe
```

`build-recovered` is a new build directory. The original ZIP retains the old `build/` cache, object files and executable; they are unnecessary for a clean rebuild and contain the original machine's absolute paths.

The program loads resources using paths such as `../shaders/basic.vert` and `../assets/textures/...`. Keep the working directory directly under `project/`, as in the example. Launching from the repository root or an IDE with a different working directory can make texture and shader loading fail.

If a locally selected GLFW linkage expects `glfw3.dll`, make the included DLL discoverable in that runtime environment. The project links by library name rather than a fully declared imported CMake target, so the selected MinGW library and architecture need to agree.

## Other platforms

The original source is preserved, but its CMake link targets and bundled GLFW binaries are Windows-specific. This archive does not provide a tested macOS or Linux port. A port would need native GLFW/OpenGL linking and platform-appropriate context creation, and should be recorded separately from the original submission.

On the archive machine, every original C++ translation unit was checked using `clang++ -std=c++17 -fsyntax-only` with the bundled include directory. The GLAD source was checked as C11. These checks passed; they do not link GLFW, create an OpenGL context, compile shaders through a driver or validate rendered pixels.

## Runtime checks after a successful build

Confirm that the scene loads its skybox, ground and three statue textures; that WASD, mouse look and scroll operate; and that F/G toggle their light contributions. Check the five-waypoint bee patrol, facial changes near statues and M/1/2/3 shortcuts. The original screenshot provides a visual reference, not a guarantee of exact appearance across graphics drivers.

The original README's statement that the project was successfully compiled is retained as submitted evidence. A fresh successful Windows build has not been claimed in this archive.
