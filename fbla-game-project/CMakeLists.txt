# CMakeList.txt : CMake project for fbla-game-project, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
include_directories("../include")
link_directories("../lib")
add_executable (game32 "main.cpp" "game.cpp" "game.h" "sprite.cpp" "sprite.h" "aabb.cpp" "aabb.h" "level.cpp" "level.h" "convar.h")
target_link_libraries(game32 raylib)
target_link_options(game32 PRIVATE -mwindows)

# TODO: Add tests and install targets if needed.
