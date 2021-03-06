# Open Source Renderer (WIP)
Implementation of physically based ray tracing alorithm. To raster image it uses an implementation
of the Reinhard global operator tone mapping. There are no dependencies and is cross compatible.

Here is a sample results so far (not full render just quick run):

![Rendered image](https://i.ibb.co/Gnwxq4Y/render.jpg)

TODO:
 - [X] Implement Reinhard Tone Mapping
 - [X] Write to PPM
 - [X] Perspective Camera
 - [X] Intersection Calculations
 - [X] Emission Spectra
 - [X] Implement Diffuse BSDF
 - [X] Recusive Integration Calculations
 - [X] Importance Sampling
 - [X] Russian Roulette Path Termination
 - [X] Next Event estimation
 - [X] Implement Plane
 - [ ] Offload image as it renders
 - [X] Implement triangles
 - [ ] Create Unit testing framework (speed and accuracy)
 - [X] Multithreading
 - [X] Import OBJ files
 - [ ] Implement spacial mapping (log n)
 - [ ] Implement other BSDF types
 - [ ] Clean Code
