# Attribution and resource provenance

## Preserved student work

The source comes from the official Assignment1 Handin attempt associated with Yongjiang Liu. It includes the interactive scene code, shaders, resource choices, README and screenshot. The archive does not imply that bundled libraries were authored by the student.

All 513 files remain inside the unchanged original ZIP. The browsable `project/` contains 483 byte-identical files; 30 generated build files are retained only inside the ZIP. This keeps the original compiled evidence while avoiding use of an old machine-specific CMake cache as the setup instructions.

## Bundled components

| Component | Evidence in the submission |
| --- | --- |
| GLFW 3.4 | Header version and retained copyright/permission notice; Windows DLL and static/import libraries |
| GLM 1.0.2 | Version macros in `include/glm/detail/setup.hpp`; bundled mathematics headers |
| GLAD 0.1.36 | Generator header names OpenGL 3.3 core, with generation metadata and original generator URL |
| Khronos platform header | Original Khronos copyright and permission notice retained |
| stb_image 2.30 | Header version and original MIT/public-domain alternatives retained |

No top-level project license or standalone GLM license file was found in the submitted archive. Existing notices are preserved. This repository does not grant new rights on behalf of component authors.

## Images and textures

The submission includes six cubemap faces, ground diffuse/specular textures, stone/metal/wood diffuse/specular and face textures, and one screenshot. Their original download URLs, creators and asset-specific permissions are not documented in the recovered README or source. Their provenance is therefore recorded as unknown rather than assigned to an invented source.

All 21 packaged images were decoded and checked during recovery. No GPS EXIF field was found, and the submitted screenshot shows the rendered scene rather than a desktop containing other applications. These checks do not establish asset ownership or public redistribution rights. The repository remains private.

## Privacy and original build evidence

The original build files contain Windows toolchain paths and the submitting user's local project path. They remain in the unchanged private ZIP as original evidence. No hardcoded credential, external process-launch command or application network endpoint was found in the reviewed student source. The prebuilt Windows executable and library binaries were not executed during review.

Submission records omit grading fields and teacher feedback. Assignment 2 is a separately observed submitted paper. Its original PDF remains unavailable while Turnitin first-use terms confirmation awaits the user; the terms have not been accepted during this recovery. The paper is not represented as recovered until its original PDF is obtained.
