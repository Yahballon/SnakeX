# SnakeX by YAHBALLON 🐍🪩

Native offline PlayStation 5 homebrew Snake game featuring a neon jungle, a smooth animated Disco Mode, and an increasing speed challenge for every apple you eat.

![Build](https://github.com/Yahballon/SnakeX/actions/workflows/build.yml/badge.svg)

## Features
- **Disco Mode:** a fourth selectable mode with slowly cycling neon/rainbow colors on the snake and outer frame, plus gently moving colored light bars across the board. Not a rapidly flashing strobe.
- **Progressive apple speed:** every consumed fruit accelerates the snake in every mode. Each apple shortens the current move interval by ~3.5%, down to a bounded minimum of 75 milliseconds. Taking a new game resets the apple boost, while keeping the chosen difficulty.
- **Classic:** avoid walls and your own tail.
- **Zen:** no collisions; wraparound and relaxed gameplay.
- **Sprint:** higher base speed, then progressively faster after each fruit.
- 24 × 24 live grid, animated pixel snake, three fruit sprites, local high score and game over.
- Settings: 8 speed levels, walls ON/OFF, fruit Apple/Cherry/Golden.
- Original 1920 × 1080 generated jungle image and 512 × 512 PS5 launcher icon.
- Fully offline; native C++ / PS5 OpenGL using the community PS5-DevBridge and ps5-homebrew-ui toolchain.

## Controller
| Input | Action |
| --- | --- |
| D-Pad / left stick | Menu navigation or change snake direction |
| Cross | Select or pause/resume |
| Circle | Back / pause |
| Options | Pause/resume |
| Square (home) | Quick start |
| Triangle (pause) | Restart |
| D-Pad left/right (settings) | Change options |

Choose **Game Mode → DISCO → X**, then **Play Game** to experience the color-cycling mode.

## Installation & update

Get `PPSA99846.zip` from [Releases](https://github.com/Yahballon/SnakeX/releases). Extract the `PPSA99846` folder and copy it into `/data/homebrew/` on an already homebrew-capable PS5 using your existing compatible loader.

**Upgrading from Snake v0.1.0:** The Title ID remains `PPSA99846`, as does Content ID `UP9000-PPSA99846_00-SNAKEHOMEBREW001`. This is an in-place upgrade, **not a second app**. Old save data stays at `/data/SnakeGame/save.ini`; do not delete it. Old high scores and settings are read by the new version. The Disco mode value uses the new ID 3; Classic/Zen/Sprint keep IDs 0/1/2.

## Build source

The build workflow is at `.github/workflows/build.yml` and creates real native `eboot.bin` with `PS5-DevBridge/templates/simple-calc` plus pinned OpenGL SDK setup, performs C++ regression tests, generates assets with Pillow and verifies the PS5 install ZIP.

Run host gameplay tests:
```sh
g++ -std=c++20 -O2 -Wall -Wextra -Werror tests/game_test.cpp -o /tmp/snakex-tests
/tmp/snakex-tests
```

Expected install layout:
```text
PPSA99846/
  eboot.bin
  sce_sys/param.json
  sce_sys/icon0.png
  sce_module/libc.prx
  assets/fonts/inter-semibold.huifont
  assets/jungle.jpg
```

Diagnostics remain at `/data/SnakeGame/game.log`.

## Version and provenance

- **SnakeX v0.2.0** (PS5 Title ID: `PPSA99846`)
- Native game, copyright © YAHBALLON, licensed GPL-3.0-or-later; `LICENSE` contains the full license.
- Migrated and extended from the [working original Snake source](https://github.com/Yahballon/tmp_lap/tree/main/homebrew/snake), also GPL-3.0-or-later. Preserve upstream provenance and the third-party PS5-DevBridge / ps5-homebrew-ui notices.
- PS5 console compatibility and behavior need testing on a real homebrew PS5; CI compilation alone does not prove a hardware test.

## Changelog
See [RELEASE_NOTES.md](RELEASE_NOTES.md).
