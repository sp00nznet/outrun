# OutRun Online Arcade — PC Recompilation

> Coastal highway, branching forks, a red Ferrari, and Magical Sound Shower — native on PC.

A static recompilation of **OutRun Online Arcade** (Sega / Sumo Digital, Xbox 360 /
XBLA, 2009) to a native x86-64 executable. The game's PowerPC code is translated
to C++ ahead of time with the [ReXGlue SDK](https://github.com/rexglue/rexglue-sdk)
and compiled to run directly on your machine — no emulator.

## Why this game

OutRun Online Arcade is the definitive modern OutRun: Sumo Digital's beautiful HD
take on *OutRun 2 SP*, with the branching A-to-E routes, the drift-happy handling,
Ferraris, and the all-time-great soundtrack — *Magical Sound Shower*, *Splash Wave*,
*Passing Breeze*. Cruise, don't commute.

And it is **one of the most infamous delistings in Xbox Live history.** Sega's
Ferrari license expired and the game was pulled in **2011** — it has been impossible
to buy for **over a decade**, and it never released on PC. For a game this beloved
to simply vanish is the textbook case for recompilation: this is, realistically, the
only way to play it on a PC at all.

## Status

🚧 **Scaffolding.** The Xbox 360 binary recompiles cleanly to C++ (base
`0x82000000`, 11.1 MB image, ~3,400 assets) via ReXGlue v0.8.0's codegen — with
**zero** manual fixups (clean codegen, no hints needed). Next up is building, then
GPU/audio/input bring-up.

| Stage | State |
|---|---|
| Extract (STFS → XEX) | ✅ |
| Codegen (PPC → C++) | ✅ (0 hints — clean) |
| Build / link | ⏳ |
| Boot / render / play | ⏳ |

## Building

You bring your own legally-dumped copy of the game — **no game data is included in
this repo** (and never will be).

```bash
# 1. Build the ReXGlue SDK (see its repo); have Clang 20+, CMake 3.25+, Ninja.
# 2. Extract your dumped package's XEX + assets to extracted/.
# 3. Recompile and build:
rexglue codegen
cmake --preset win-amd64-release
cmake --build out/build/win-amd64-release
# 4. Run:
./out/build/win-amd64-release/outrun.exe --game_data_root=extracted
```

Tooling and the full workflow live in [360tools](https://github.com/sp00nznet/360tools).

## Legal

This repository contains only original recompilation scaffolding and code. It
includes **no** game assets, executables, or copyrighted material. OutRun Online
Arcade is © Sega; OutRun and Ferrari trademarks belong to their respective owners.
Supply your own legally-obtained copy.
