# SnakeX v0.2.1 — 16-bit Retro Jungle Audio

## New
- Real native **SDL2** PS5 music output, using an original procedural 16-bit-style jungle synthesizer (no copyrighted music or network downloads).
- Retro jungle soundtrack blending digital bird chirps, crickets, breeze, hollow drum rolls, kick/hat percussion, chip bass and tropical chiptune melody.
- In-game SFX for apples, menu navigation, game start and game over.
- In Disco mode, the jungle percussion groove is slightly more upbeat.
- New native settings: Jungle Music On/Off, Sound Effects On/Off, Master Volume 0–10. Audio settings persist alongside high scores and game options.
- Native host regression test for non-silent output, effects, muting, disco waveform and volume safety.

## Technical
- SDL2 audio device queues bounded, generated 48 kHz signed 16-bit stereo PCM. Audio code has a zero-allocation synthesis loop.
- Safely degrades to silent gameplay if PS5 audio initialization fails (see `/data/SnakeGame/game.log`).
- Keeps Title ID `PPSA99846`, Content ID `UP9000-PPSA99846_00-SNAKEHOMEBREW001`, and existing `/data/SnakeGame/save.ini`.
- Native PlayStation 5 compilation and ZIP validation via GitHub Actions; real-hardware test required separately.
