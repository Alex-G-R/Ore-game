cmake_minimum_required(VERSION 3.24)
project(SFML_Coal)

set(CMAKE_CXX_STANDARD 14)

add_executable(SFML_Coal main.cpp
        Game.h
        Game.cpp
        Player.h
        Player.cpp
        Tilemap.cpp
        Tilemap.h
        Camera.cpp
        Camera.h
        Tilemap.cpp
        Tilemap.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/dev/DEVEL/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/dev/DEVEL/SFML/include/SFML)
target_link_libraries(SFML_Coal sfml-system sfml-window sfml-graphics sfml-audio)