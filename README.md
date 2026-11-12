# Checkers

A checkers game written in C++ using SFML.

Built for fun -- it has a few quirks I decided to keep as features.

Created December 2021.

---

## Running it

It builds two ways from the same code: **Visual Studio** (`Checkers.sln`, as before) or **CMake**, which works for the terminal and VS Code
on Linux/macOS. Visual Studio ignores `CMakeLists.txt`, so the two don't interfere.

### What you need (CMake)
A C++17 compiler, CMake ≥ 3.16 and SFML 2.5 or 2.6. On Ubuntu:
```bash
sudo apt install build-essential cmake libsfml-dev
```

### Quickest: `run.sh`
```bash
./run.sh
```
This builds (only what changed) and starts the game. Use `./run.sh --clean` to wipe `build/` and rebuild from scratch first.

### From the terminal, step by step
```bash
cmake -S . -B build
```
```bash
cmake --build build
```
```bash
cd build && ./Checkers
```
Run it from inside `build/`. The game loads `Assets/arial.ttf` from there, and CMake links `build/Assets` to `Checkers/Assets`.

### From VS Code
1. Open this folder in VS Code. Install the recommended **C/C++** and **CMake Tools** extensions if asked.
2. When CMake Tools asks for a *kit*, pick **GCC**.
3. Click **Build** in the bottom status bar, then **▷ Run** (or the 🐞 button to debug with breakpoints).

### From Visual Studio
Open `Checkers.sln` as before.

---

## Controls
| Input | Effect |
|---|---|
| **Left click** a piece of the team whose turn it is | Select it |
| **Left click** a dark square | Move or jump there |
| **Left click** the selected piece again | Deselect it, or end your turn after a jump |
| **Esc** / close window | Quit |

The square in the top-left corner shows whose turn it is.

---

## Notes for building outside Visual Studio
These small changes made the code build with g++ as well as MSVC:
- `stdafx.h` includes the Windows-only `targetver.h` / `<tchar.h>` only when `_WIN32` is defined.
- `piece.cpp`: `sf::Color::Color(...)` became `sf::Color(...)`. Only MSVC accepts the first form.
- `board.cpp`: `#include "Board.h"` became `"board.h"`, to match the real file name on case-sensitive file systems.
