# Wolf3D

This project consists of developing a 3D first-person shooter game inspired by the classic **Wolfenstein 3D**, built from scratch in **C** using the **CSFML** graphic library and the **raycasting** rendering technique (using the `Digital Differential Analysis - DDA` algorithm).

The application delivers a complete gaming experience featuring:
- textured walls, floor and ceiling
- animated enemy sprites
- collision detection
- interactive weapon mechanics with recoil and bobbing
- a full HUD (health, ammunition, crosshair)
- dynamic lighting/flashlight
- a particle system for visual effects
- a game save/load system.

## Technical Requirements and Features Implemented
- **Raycasting and DDA:** precise wall projection utilizing player direction and camera plane vectors.
- **Framerate Independence:** all movements, enemy tracking, and weapon/particle animations are scaled by delta time (`dt`).
- **Full Feature Set**
    - Main menu, settings (volume control), and save/load game.
    - HUD displaying health and ammunition bars alongside a targeting crosshair.
    - Flashlight toggle and sound/music effects.
    - Minimap displaying player and enemy locations.
- **Error Handling and Robustness:** writes runtime errors to `stderr` and exits with code `84` on critical failures or `0` on success.

## Project Structure
- `include/`
    - `raycast.h`         # Header file specifically for raycasting logic
    - `wolf3d.h`          # Main header file for global structures and functions
- `src/`
    - `drawing/`
        - `ceiling.c`     # Floor and ceiling perspective drawing routines
        - `drawing.c`     # Pixel buffer manipulation and lighting calculations
        - `floor.c`       # Floor surface rendering routines
    - `enemy/`
        - `enemy.c`       # Enemy sprite projection and rendering logic
        - `movement.c`    # Enemy movement, sorting, and animation updates
    - `weapon/`
        - `ammunition.c`  # HUD ammunition bar and crosshair rendering
        - `shoot.c`       # Wall shooting and interactive destruction logic
        - `weapon.c`      # Weapon creation, update, and rendering logic
    - `events.c`          # Keyboard and mouse event polling
    - `health.c`          # Player health tracking and game over screen
    - `main.c`            # Entry point and main game loop orchestrator
    - `map.c`             # Map file parsing and tile loading
    - `menu.c`            # Main menu and settings interface components
    - `mini_map.c`        # Minimap view and radar rendering
    - `particles.c`       # Particle system pool, update, and explosion logic
    - `player.c`          # Player creation, movement, rotation, and collision detection
    - `raycast.c`         # Raycasting and DDA wall-finding logic
    - `save.c`            # Game state file saving and loading system
    - `sound.c`           # Sound effects and background music management
    - `window.c`          # Window creation and fullscreen toggle handling
    - `wolf3d.c`          # Initialization and cleanup of the core engine
- `utils/`                # Asset files including textures (walls, floors, ceilings, enemies), weapon sprites, fonts (`arial.ttf`), and audio tracks
- `Makefile`              # Compilation rules for building (all), cleaning (clean, fclean) and rebuilding (re) the project.
- `README.md` 

## Compilation and Usage
**BUILD**
To compile the `wolf3d` binary using the provided Makefile, run: make.
To clean intermediate or target files:
- `make clean`  # Removes object files.
- `make fclean` # Removes object files and binaries.
- `make re`     # Clean rebuild.

**USAGE**
Run the game executable: ./wolf3d

**CONTROLS**
- **W, A, S, D:** move forward, rotate left, move backward, rotate right.
- **LShift:** run (increases movement speed and weapon bobbing intensity).
- **Space:** fire weapon / interact with the environment.
- **L:** turn flashlight on/off.
- **F:** toggle fullscreen mode.
- **ESC:** return to main menu.
