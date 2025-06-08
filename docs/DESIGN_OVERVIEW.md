# Design Overview

This document outlines the technical vision for the HOI4-inspired prototype.

## Engine
- Lightweight C++17 engine
- Custom ECS with std::unordered_map storage
- Event bus for decoupled systems
- SDL2 + OpenGL graphics backend
- ImGui for developer UI

## Game
- World map split into states described in JSON
- Real-time with adjustable speed factors
- Countries have basic economy and politics variables
- AI uses simple evaluation to assign behaviors
- Game state serializes to compressed JSON

## Tools
- Map compiler converts SVG shapes into binary mask format
- Save converter upgrades save files between versions

## Future Work
- Expand AI behaviors
- Implement combat and supply calculations
- Add multiplayer networking
