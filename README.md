# labeeri

A C++ game engine (because I hate myself).

Originally made for the BI-PGR.21 (B0B39PGR) course at FIT/FEE CTU as a semestral project.

## Features

- Scriptible ECS architecture
- Resource management
- Event system
- HDR pipeline
- Transparency
- Normal maps
- Postprocessing
- Object picking via ID buffer
- ImGui window system
- OpenGL backend
- Extendable render API support

<p align="center">
  <img src="./.images/maxwell.gif">
</p>

WebGPU backend and Rust rewrite coming soon???

## Installation

- C++20
- Visual Studio 2022

The project uses Vcpkg for all dependencies (vcpkg.json), Visual Studio should install them for you automagically.

## Docs

Can be generated with Doxygen.

```sh
doxygen
```

## The Game

A simple labyrinth with interesting objects in each room. I would like to add infinite generation and random mesh generation. :)

<p align="center">
  <img src="./.images/main_view.png">
</p>

<p align="center">
  <img src="./.images/fisheye.png">
</p>

### Running

Download and run the [latest release](https://github.com/cernymichal/labeeri/releases).

Everything except for the standard library is linked statically for now, so you shouldn't have any dependancy issues (C++ redist is provided).

### Controls

- Click in the scene - enter FPS mode
- ESC - exit FPS mode
- WASD - movement
- Left shift - run
- Ctrl / Space - vertical movement (only in free camera)
- Left click - interact with an object
- F - toggle flashlight
- F1 - free camera / player camera
- F3 - toggle GUI overlay
- F5 - fullscreen
- Page up / Page down - switch between static cameras
- Ctrl + left click on object - edit object (only in GUI mode)
