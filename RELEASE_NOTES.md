# SnakeX v0.2.0 — Disco Mode & Apple Acceleration

Native PS5 homebrew, by YAHBALLON.

## New
- **Disco mode:** fourth playable mode with a smooth shifting neon-rainbow snake, animated playfield light bars, and color-changing frame. Slow color transitions instead of strobing. Gameplay rules match Classic.
- **Every fruit makes the snake faster** in Classic, Zen, Sprint and Disco, independently of fruit type. The pace ramps multiplicatively with a safe minimum tick interval, and resets at the start of the next game.
- Renamed in the PS5 app tile and in-game UI to **SnakeX**. New generated original game logo / PS5 icon.
- Added regression tests for incremental acceleration and all four modes.

## Compatibility
- Preserves **PPSA99846** and original Content ID (`UP9000-PPSA99846_00-SNAKEHOMEBREW001`) so the existing installed game can be upgraded in place.
- Preserves `/data/SnakeGame/save.ini` (high score, settings and selected mode); old mode IDs remain valid.
- No new permissions or network required.
- Moved maintained source from `Yahballon/tmp_lap/homebrew/snake` to standalone `Yahballon/SnakeX`. Code derived from the v0.1.0 GPL-3.0-or-later edition with attribution preserved.

## Build & test
The GitHub workflow runs host regressions, generates art, cross-compiles the native PS5 ELF and verifies the installable `PPSA99846.zip`. The physical PS5 hardware test is separate and not implied by a green GitHub Actions build.
