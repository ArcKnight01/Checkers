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

## How the code works

```
Checkers/
  Checkers.cpp     main(): window, creates the board, game and 24 pieces, runs the game loop
  board.h/.cpp     class Board: the 8×8 grid, which tile was clicked, drawing the squares
  game.h/.cpp      class Game: whose turn it is, piece counts, the victory message
  piece.h/.cpp     class Piece: one checker; selecting, moving, jumping, kinging
  stdafx.h/.cpp, targetver.h   Visual Studio leftovers (precompiled-header template)
  piece CPP.txt    an older backup copy of piece.cpp
  Assets/arial.ttf font for the victory message
```

**Tiles are numbered 0–63**, left to right then top to bottom, so tile `i` is at column `i % 8`, row `i / 8`. Moves are
tile-number arithmetic: one row down-left is `+7`, down-right `+9`, and a jump is double that (`+14`, `+18`). Up is the same
with minus.

**`main()` (Checkers.cpp)**
1. Creates the `Board` (800×800, 8×8), the `Game` (12 pieces per team) and 24 `Piece`s in a `std::vector<Piece> checker`.
   Red start on the top three rows, white on the bottom three: `spawnPos` picks the dark squares, and white is mirrored with
   `tileCount - 1 - spawnPos`.
2. Builds `checkerPtr`, a list of **pointers** to those pieces. Each piece gets it so it can check where the others are.
3. Every frame: reads the mouse click (`getTileN` turns the click into a tile number), draws the board and the turn indicator,
   then calls `update()` and `drawPiece()` on every live piece. A captured piece is counted (`losePiece`) and skipped from then
   on, and the victory text shows when a team runs out.

**`Board`**: `tileTypes` marks each square `black` (playable) or `white`. `getTileN(x, y)` converts pixels to a tile number;
`getTilePos(n)` converts a tile number to pixels. `newClick`, `clickPos` and `pieceJumping` are shared flags the pieces read.

**`Game`**: `turncolor` is whose turn it is (`redteam` / `whiteteam`), and `changeTurn()` flips it and recolours the square in
the top-left corner. `pieceTotal[]` counts pieces left; `losePiece()` returns `true` when a team hits 0.

**`Piece`**: holds pointers back to the board and game (`boardref`, `gameref`), its `position` (tile number), `color`, and the
flags `alive`, `selected` and `kinged`.
- `selectPiece()`: clicking your own piece on your turn selects it (green outline); clicking it again deselects it, or ends your
  turn after a jump.
- `placePiece()`: with a piece selected, a click on an empty dark square is checked against the legal moves. Red moves down,
  white moves up, kings both ways. A jump sets the jumped piece's `alive = false` and lets you keep jumping
  (`pieceJumping`). Reaching the far row kings the piece.
- `drawPiece()`: draws the circle, an inner ring, and a crown (`kingShape`) for kings.

---

## Notes for building outside Visual Studio
These small changes made the code build with g++ as well as MSVC:
- `stdafx.h` includes the Windows-only `targetver.h` / `<tchar.h>` only when `_WIN32` is defined.
- `piece.cpp`: `sf::Color::Color(...)` became `sf::Color(...)`. Only MSVC accepts the first form.
- `board.cpp`: `#include "Board.h"` became `"board.h"`, to match the real file name on case-sensitive file systems.
