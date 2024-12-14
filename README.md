# Orbit Simulator

A C++ simulation of orbital mechanics featuring various satellites and space objects around Earth.

## Overview

This simulator models the behavior of various satellites and spacecraft in Earth's orbit. It includes realistic physics calculations for orbital mechanics, collision detection, and object fragmentation.

## Features

- Real-time orbital physics simulation
- Multiple satellite types:
  - Crew Dragon
  - GPS satellites
  - Hubble Space Telescope
  - Starlink satellites
  - Sputnik
- Player-controlled spacecraft
- Collision detection and object fragmentation
- Real-world physics calculations including:
  - Gravitational effects
  - Orbital mechanics
  - Velocity and acceleration
- Visual representation of Earth and space objects

## Class Structure

### Core Classes
- `Object`: Base class for all physical objects in the simulation
- `CelestialObject`: Base class for all orbital objects
- `Satellite`: Base class for all satellite types
- `Part`: Class representing satellite fragments after collisions
- `Fragment`: Class for debris particles

### Satellite Types
- `Dragon`: SpaceX's Crew Dragon spacecraft
- `GPS`: Global Positioning System satellites
- `Hubble`: Hubble Space Telescope
- `Starlink`: SpaceX's internet satellites
- `Sputnik`: First artificial satellite

### Physics Classes
- `Physics`: Handles orbital mechanics and gravity calculations
- `Position`: Manages object positions
- `Velocity`: Handles object velocities
- `Acceleration`: Manages object accelerations
- `Angle`: Handles angle calculations and normalization
- `Direction`: Manages directional calculations

### Simulation Management
- `Simulator`: Main simulation controller
- `Fragment`: Handles debris generation and management

## Dependencies

- OpenGL
- GLUT
- C++ Standard Library

## Setup

1. Ensure you have a C++ compiler installed
2. Install OpenGL and GLUT libraries
3. Clone the repository
4. Build using your preferred C++ compiler or IDE

### Windows Setup
```bash
# Using Visual Studio
1. Open the .sln file
2. Build solution (F7)
3. Run (F5)
```

### Linux/Unix Setup
```bash
# Using g++
g++ -o simulator main.cpp [other .cpp files] -lglut -lGL -lGLU
./simulator
```

## Controls

- Arrow Keys: Control spacecraft direction
- Space: Fire projectile
- Down Arrow: Apply thrust
- Left/Right Arrows: Rotate spacecraft

## Testing

The project includes comprehensive unit tests for all major components:
- Acceleration tests
- Angle tests
- Celestial Object tests
- Direction tests
- Dragon tests
- Fragment tests
- GPS tests
- Hubble tests
- Part tests
- Physics tests
- Projectile tests
- Satellite tests
- Ship tests
- Sputnik tests
- Starlink tests
- Velocity tests

Run tests using the test runner in main.cpp.

## Physics Implementation

The simulation uses real-world physics formulas for:
- Gravitational force calculation
- Orbital velocity computation
- Collision detection
- Object fragmentation
- Trajectory calculation

## Authors
- Chris Mijangos
- Seth Chen

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

MIT License
