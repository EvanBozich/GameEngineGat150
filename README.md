# Game Engine

A component-based 2D game engine written in C++20, built with SDL3, FMOD, Box2D, and RapidJSON. Includes a demo game showcasing the engine's core systems.

## Features

- **Component-Based Architecture** — Actors are composed of modular components rather than deep inheritance hierarchies, enabling flexible and reusable game object design.
- **Audio System** — Powered by FMOD for sound effects, music, and mixing.
- **Input System** — Unified handling of keyboard, mouse, and controller input via SDL3.
- **Physics System** — 2D rigid body physics and collision detection powered by Box2D.
- **Renderer** — SDL3-based 2D rendering pipeline.
- **Serialization** — Scene, actor, and component data loaded/saved using RapidJSON.
- **Demo Game** — A sample project demonstrating actors, components, tilemaps, and UI built on top of the engine.

## Tech Stack

| Purpose        | Library     |
|----------------|-------------|
| Windowing / Input / Rendering | [SDL3](https://www.libsdl.org/) |
| Audio          | [FMOD](https://www.fmod.com/) |
| Physics        | [Box2D](https://box2d.org/) |
| Serialization  | [RapidJSON](https://rapidjson.org/) |
| Language       | C++20 |

## Architecture Overview

```
Engine
├── Core
│   ├── Actor
│   ├── Component
│   └── Scene
├── Systems
│   ├── AudioSystem      (FMOD)
│   ├── InputSystem      (SDL3)
│   ├── PhysicsSystem    (Box2D)
│   └── RenderSystem     (SDL3)
├── Serialization
│   └── JSON Loader/Writer (RapidJSON)
└── Demo Game
    ├── Actors
    ├── Components
    ├── Tilemaps
    └── UI
```

### Actors & Components

Actors are lightweight containers that hold a collection of components. Each component encapsulates a single piece of behavior or data (e.g., `SpriteComponent`, `RigidBodyComponent`, `AudioComponent`), which are updated and rendered by their respective systems each frame.

### Systems

- **AudioSystem** — Wraps FMOD to load and play sound banks/events, manage channels, and handle 2D/3D audio positioning.
- **InputSystem** — Polls SDL3 input events and exposes a simple query API (key/button down, pressed, released) to components.
- **PhysicsSystem** — Steps the Box2D world, syncs transforms between physics bodies and actors, and dispatches collision events.
- **RenderSystem** — Manages the SDL3 render pipeline, sprite batching, camera, and draw order.

### Serialization

Scenes, actors, and components are described in JSON and parsed with RapidJSON, allowing levels and prefabs to be authored as data rather than hardcoded in C++.

## Demo Game

The included demo game demonstrates the engine in practice:

- **Actors** — Player, enemies, and interactive objects built from engine components.
- **Components** — Custom gameplay components layered on top of the core engine components.
- **Tilemaps** — Grid-based level layout with collision integration via Box2D.
- **UI** — In-game HUD and menu elements rendered through the RenderSystem.

## Getting Started

### Prerequisites

- Visual Studio 2022 (with the "Desktop development with C++" workload, C++20 support)
- SDL3
- FMOD Engine SDK
- Box2D
- RapidJSON

### Build

1. Clone the repository.
2. Open `GameEngine.sln` in Visual Studio.
3. Ensure the third-party dependencies (SDL3, FMOD, Box2D, RapidJSON) are available and correctly referenced in the project's include/library paths.
4. Select the desired configuration (Debug/Release) and platform.
5. Build the solution (`Build > Build Solution`, or `Ctrl+Shift+B`).

### Run

- Run directly from Visual Studio by setting **Game** as the startup project and pressing `F5` / `Ctrl+F5`.
- Alternatively, run the built executable directly from the output build folder (e.g. `build/Game.exe`), once compiled.

## Project Structure

The solution is split into two projects: **Engine** (the reusable engine library) and **Game** (the demo game built on top of it).

```
GameEngine.sln
├── Engine
│   ├── Audio
│   ├── Components
│   ├── Core
│   ├── Framework
│   ├── Input
│   ├── Math
│   ├── Physics
│   ├── Renderer
│   ├── Resource Files
│   ├── Resources
│   ├── Serialization
│   ├── Engine.cpp / Engine.h
│   ├── framework.h
│   └── pch.cpp / pch.h
└── Game
    ├── Header Files
    ├── Resource Files
    ├── Source Files
    ├── SpaceGame
    ├── SpriteGame
    └── Main.cpp
```


## Acknowledgments

- [SDL3](https://www.libsdl.org/)
- [FMOD](https://www.fmod.com/)
- [Box2D](https://box2d.org/)
- [RapidJSON](https://rapidjson.org/)
