# 3D Computer Graphics — COM6503

An archive of Yongjiang Liu's COM6503 coursework at the University of Sheffield, cross-listed with COM3503 and COM4503.

**Assignment 1: The Buzzing Scene** is a C++17 / OpenGL 3.3 interactive scene. A bee assembled from transformed sphere meshes patrols around three textured statues, which change their facial textures when the bee approaches. The scene includes a textured ground, rotating cubemap skybox, interactive camera and two switchable light contributions.

The recovered [source project](project/) includes the original shaders, textures, bundled libraries and screenshot. Its files are unchanged from the official Assignment 1 ZIP, apart from omitting generated build files from the browsable tree; those remain preserved inside the original archive.

![Original screenshot included in the submitted ZIP](project/yongjiangliu_screenshot.png)

*Original submission screenshot. The scene has not been rerendered during archiving.*

## Scene and interaction

| Feature | Implementation |
| --- | --- |
| Bee modelling | Body-relative matrices position and animate the head, eyes, antennae, tail and wings. |
| Motion | A five-waypoint patrol, direction-facing rotation, sinusoidal wing motion and a visual hovering offset. |
| Statue reactions | Stone, metal and wood appearances; the face changes when the bee is within four scene units. |
| Lighting | Phong-style ambient/diffuse/specular terms, a positional general light and a spotlight at a fixed origin whose direction sweeps around the scene. |
| Environment | Textured ground and a slowly rotated cubemap view. |
| Camera | Keyboard movement, mouse look and scroll-controlled field of view. |

| Input | Action |
| --- | --- |
| W / A / S / D | Move the camera |
| Mouse / scroll | Look around / adjust field of view |
| F / G | Toggle spotlight / general light |
| M | Enable or disable the pose-position shortcuts |
| 1 / 2 / 3, while pose mode is enabled | Set the bee near the stone / metal / wood statue |
| Esc | Close the window |

Pose mode still calls the patrol update in the submitted implementation. Its position shortcuts do not permanently freeze the bee. The [implementation notes](docs/IMPLEMENTATION.md) describe this and other preserved limitations.

## Build and verification

The submitted build targets **Windows x64 with MinGW, Ninja and OpenGL**. Start with the [build instructions](docs/BUILD.md); launch from a directory directly inside `project/` so the original relative resource paths resolve.

All nine C/C++ translation units passed syntax checks with Apple clang during recovery. All packaged images and referenced scene resources were checked. Windows linking, shader compilation in a live OpenGL context and interactive rendering have not been verified on the archive machine. The original Windows executable is preserved within the ZIP and was not executed during review.

## Submission coverage

| Assessment | Recovered content | Status |
| --- | --- | --- |
| Assignment1 Handin | Official ZIP, C++ scene, shaders, resources, bundled dependencies and original screenshot | Preserved; submitted 10 December 2025 at 22:15 (UTC+8) |
| Assignment2 | A submitted Turnitin paper named `yongjiang_elp25aai_com6503.pdf` was observed | Original PDF not recovered: Turnitin first-use terms confirmation awaits the user; its contents are not archived or summarized |

The [Assignment 2 observation record](archive/assignment2/submission_record.json) preserves the observed submission details. No file hash is claimed for a PDF that has not been downloaded. The current repository does not claim that every course deliverable has been recovered.

## Archive guide

- [Original Assignment 1 ZIP](archive/assignment1/3d_graphing_programme.zip) and [submission record](archive/assignment1/submission_record.json): unchanged download and hashes for every submitted file.
- [project/](project/): source, shaders, assets, dependencies and the original README. Use this repository's build notes for the clarified setup.
- [Implementation notes](docs/IMPLEMENTATION.md): source map and actual behaviour.
- [Attribution and resources](docs/ATTRIBUTION.md): third-party components, asset provenance and preservation boundaries.
- [Verification record](docs/verification.json): checks performed and their limits.

This is a private preservation repository. The original asset sources are not documented in the submission; the archive does not claim ownership of third-party libraries or textures.
