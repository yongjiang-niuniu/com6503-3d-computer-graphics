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

## Assignment 1 images and textures

The submission includes six cubemap faces, ground diffuse/specular textures, stone/metal/wood diffuse/specular and face textures, and one screenshot. Their original download URLs, creators and asset-specific permissions are not documented in the recovered README or source. Their provenance is therefore recorded as unknown rather than assigned to an invented source.

All 21 packaged images were decoded and checked during recovery. No GPS EXIF field was found, and the submitted screenshot shows the rendered scene rather than a desktop containing other applications. These checks do not establish asset ownership or grant new redistribution rights. The owner has authorized publication of the submitted coursework archive; its original resource attribution and documented source gaps remain unchanged.

## Privacy and original build evidence

The original build files contain Windows toolchain paths and the submitting user's local project path. They remain in the unchanged original ZIP as evidence. No hardcoded credential, external process-launch command or application network endpoint was found in the reviewed student source. The prebuilt Windows executable and library binaries were not executed during review.

Submission records omit grading fields and teacher feedback. Both original assignment attachments have now been recovered. The Assignment 2 PDF retains the original author declaration, email and student identifier as part of the owner-authorized original submission; these identifiers are not repeated in the README. The assignment receipt's reference to a private archive describes its recovery-time state. That historical receipt remains unchanged.

## Assignment 2 report and sources

The [original Assignment 2 paper](../reports/assignment2/yongjiang_elp25aai_com6503.pdf) states that its photographic references were taken by the author with a smartphone. Its Blender PBR workflow uses material sets cited from FreePBR: scratched metal, rock wall mortar and aged wood planks. These citations establish the report's stated sources, not the provenance of the different image files inside the Assignment 1 ZIP.

The paper describes the external materials as permissively licensed/CC0. The archive preserves that original wording without converting it into an independently verified license grant. The three cited product pages were reachable when checked; no original downloaded package or license file was recovered from the student's Blender working files, and no replacement material package has been added.

The original declaration, bibliography, photography notes and generative-AI statement remain intact. The [report guide](ASSIGNMENT2_REPORT.md) distinguishes the recovered PDF evidence from the missing editable Blender project.
