# Freediver's Adventures — Mega Drive prototype

This is Stage 2: a starter SGDK project for an original 16-bit underwater platform/adventure game.

## Included
- `src/main.c`: player movement, screen bounds, score, oxygen timer and treasure collision.
- `res/background.png`: 320x224 underwater cave background.
- `res/player.png`: four-frame 32x32 diver sprite strip.
- `res/treasure.png`: collectible gem sprite.
- `res/resources.res`: SGDK resource declarations.

## Build requirement
This is source code and art, not yet a compiled `.BIN` ROM. To build a Mega Drive ROM, install the Sega Genesis Development Kit (SGDK), configure its `GDK` environment variable, and run the SGDK build process for this project. A compatible 68000 toolchain is required.

## Controls
- D-pad: swim
- Start: restart after oxygen reaches zero

## Next development stage
Add proper animation timing, collectible treasure graphics, enemies, level transitions, sound effects, title screen and tested collision/oxygen balancing.
