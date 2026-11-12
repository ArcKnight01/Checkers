# CMake build for Linux/macOS/VS Code. Visual Studio users can keep using Checkers.sln:
# Visual Studio ignores this file unless you open the folder with File > Open > Folder.
cmake_minimum_required(VERSION 3.16)
project(Checkers CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)   # breakpoints work out of the box
endif()

# SFML 2.5+ (Ubuntu: sudo apt install libsfml-dev)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Checkers
  Checkers/Checkers.cpp
  Checkers/board.cpp
  Checkers/game.cpp
  Checkers/piece.cpp
)
target_link_libraries(Checkers PRIVATE sfml-graphics sfml-window sfml-system)

# The game loads "Assets/arial.ttf" relative to the folder it runs from (build/),
# so link build/Assets back to the repo's Checkers/Assets.
file(CREATE_LINK ${CMAKE_SOURCE_DIR}/Checkers/Assets ${CMAKE_BINARY_DIR}/Assets SYMBOLIC COPY_ON_ERROR)
