cmake_minimum_required(VERSION 3.24)
project(SFML_Ore)

set(CMAKE_CXX_STANDARD 14)

add_executable(SFML_Ore main.cpp
        Game.h
        Game.cpp
        Tilemap.cpp
        Tilemap.h
        Camera.cpp
        Camera.h
        Tilemap.cpp
        Tilemap.h
        Tileselector.cpp
        Tileselector.h
        UI_info.cpp
        UI_info.h
        Tile.cpp
        Tile.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/dev/DEVEL/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/dev/DEVEL/SFML/include/SFML)
target_link_libraries(SFML_Ore sfml-system sfml-window sfml-graphics sfml-audio)