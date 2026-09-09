# Assignment 2: statue-material realism

**Title:** How can computer graphics renderings of statues be made to look more realistic?

**Artifact:** [Original submitted PDF](../reports/assignment2/yongjiang_elp25aai_com6503.pdf), 19 pages, submitted through Turnitin on 16 January 2026 at 20:18 (UTC+8). The file was downloaded from the submitted-paper page after the user authorized acceptance of Turnitin's first-use agreement. Its [submission record](../archive/assignment2/submission_record.json) preserves the download provenance and SHA-256.

## What the paper investigates

The report compares material appearance under a Phong-style empirical shading approach and a node-based PBR approach. The material cases are stone, weathered wood and metal. Its main evidence consists of three image triplets, each containing a real photograph, a Phong-style rendering and a PBR rendering, supported by screenshots of Blender material node graphs.

The practical appendix says the photographic references were taken by the author and that **both rendered comparison variants were prepared in Blender**. The Phong-style setup uses a photographic diffuse texture and manually adjusted lighting parameters. The PBR setup combines externally sourced material channels, including colour, roughness, metallic and normal inputs, with scaling/value adjustments where required. The appendix states that displacement mapping was not used.

The text relates the comparison to Assignment 1's lighting concepts. However, `project/` remains the original C++ OpenGL bee scene. It does not contain a recovered Blender scene or a newly implemented PBR renderer.

## Evidence map

| PDF pages | Content |
| --- | --- |
| 1–3 | Original authorship declaration, title/abstract and contents |
| 4–5 | Texture sampling, Phong reflection and introductory PBR concepts |
| 6–8 | Figures 1–3: material node-graph screenshots for the stone, wood and metal cases |
| 9–10 | Figures 4–6: photograph / Phong-style / PBR image triplets |
| 11–12 | Discussion of weathering, limitations and conclusion |
| 13 | Bibliography and external material links |
| 14–17 | Photography details and environmental-context photographs |
| 17–18 | Practical Blender setup and relationship to the first assignment |
| 18–19 | Original generative-AI declaration and acknowledgements |

The paper's interpretation is that roughness, normal and metallic information can produce more convincing material-specific shading than colour alone. This is a **qualitative visual assessment**. It supplies no numerical image-error metric, frame-time study or blinded perceptual experiment. The baseline uses the author's photographs while the PBR variant uses separately sourced material textures; the comparison therefore changes texture content as well as shading workflow. These figures should not be treated as an isolated measurement of one shader's improvement.

## Material references

The report cites these external products on page 13:

- [Scratched Metal PBR Material](https://freepbr.com/product/scratched-metal-pbr/)
- [Rock Wall Mortar PBR Material](https://freepbr.com/product/rock-wall-mortar-pbr/)
- [Aged Wood Planks PBR Material](https://freepbr.com/product/aged-wood-planks-pbr-material/)

They are material-product links, not links to the student's source code or Blender project. The pages were reachable at archive review. Their contents do not establish which precise downloaded package versions were used in January 2026. No material files were downloaded or substituted during recovery, and the report's licensing description has not been independently validated against original package licenses.

## Reproduction requirements

The preserved PDF contains visual evidence and descriptions but no embedded attachment or external student-code link. The following working artifacts are still absent:

- Original `.blend` scenes, geometry and full material node settings.
- Standalone reference photographs and the exact crops/textures used for the baseline.
- Original PBR texture packages and any local edits.
- Blender version, render engine, lighting/environment maps, camera transforms, colour management, sampling and output settings.

Rebuilding a similar scene from the report would be a new reconstruction. It would not recover the original working project or reproduce the original images exactly without those inputs. No image, experiment or rendering result has been generated to fill these gaps.

## Preservation and review

The downloaded paper is preserved byte for byte. All 19 pages were read and rendered for review, with the node graphs, comparison figures and practical appendix inspected at page scale. The PDF has no embedded file; its six external link annotations resolve to the three material products above. Existing source files in `project/` and the Assignment 1 ZIP remain unchanged.

SHA-256:

```text
804e920b8fce7e8d1db51d6a7b622c416634a716aeba25da31473f37ed3c189a
```
