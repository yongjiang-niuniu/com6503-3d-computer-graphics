# Implementation map and preserved behaviour

The descriptions below come from the submitted source, not from a new rendering run.

| File | Responsibility |
| --- | --- |
| `project/src/main.cpp` | OpenGL/GLFW initialization, camera input, scene construction, lighting uniforms and render loop |
| `project/src/Bee.cpp` | Five-waypoint patrol, body-relative component transforms, wing oscillation and hovering |
| `project/src/Statue.cpp` | Texture loading and distance-triggered face selection |
| `project/src/Sphere.cpp` | Procedural sphere geometry used for the bee, statues and light marker |
| `project/src/Ground.cpp` | Ground quad, repeated texture coordinates and ground texture loading |
| `project/src/Skybox.cpp` | Six-face cubemap loading and skybox rendering with translation removed from the view |
| `project/src/Shader.cpp` | Shader-file loading, compilation/linking and diagnostic output |
| `project/src/glad.c` | Generated third-party OpenGL function loader |
| `project/src/stb_setup.cpp` | The single stb_image implementation definition |
| `project/shaders/` | Object shading and cubemap shaders |

## Animation and materials

The bee is built from scaled sphere meshes. Each component derives its transform from a common body matrix. Wing rotation follows `sin(time × 25) × 45` degrees; the displayed body's height has a `sin(time × 3) × 0.2` offset. The logical position moves toward five fixed waypoints at a nominal speed of 1.5 scene units per second and faces its travel direction.

The statue meshes are differently scaled spheres with stone, metal and wood face textures. A distance threshold of four units selects the scared face. The scene's `assets/models/` directory is empty in the original ZIP; it does not supply imported model files. Bee body and wing textures reuse the submitted wood and metal diffuse images.

## Clarifications to the original README

The original README is preserved unchanged in `project/README.md`. Several descriptions there are broader than the source behaviour:

- The general light is labelled sunlight/directional in comments, but `basic.frag` calculates a direction from `lightPos − FragPos`. It is a positional light contribution without distance attenuation.
- The spotlight origin stays at `(0, 8, 0)`. Its target circles the scene, rotating the beam direction; the source sphere itself does not travel around the scene.
- M enables the 1/2/3 placement controls, but both render-loop branches call `bee.update(deltaTime)`. Patrol movement therefore continues in pose mode.
- The route is a fixed five-waypoint loop. It has no obstacle search or collision-avoidance algorithm.
- The skybox rotates a cubemap view. It is not a simulated cloud system.

## Limits visible in the submitted code

The window-resize callback updates the viewport, while the projection aspect ratio remains the original 800/600 value. Resizing can therefore distort the scene. Patrol movement does not clamp a step to the remaining waypoint distance, so a large frame-time jump can overshoot a target.

OpenGL object ownership is not encapsulated with destruction of every allocated buffer/texture; the application relies largely on process/context teardown. Shader-file errors are printed, and the code can proceed to shader creation afterward. The original source has not been changed to address these issues.

The archive makes no claim of physically based materials, shadows, measured performance, a general scene-graph framework or a complete cross-platform build. Its purpose is to preserve and explain the submitted implementation accurately.
