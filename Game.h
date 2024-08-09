
#ifndef GAME_H
#define GAME_H

#include <Graphics.hpp>
#include <System.hpp>
#include <Window.hpp>
#include <Audio.hpp>
#include <Network.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "Camera.h"
#include "Tilemap.h"
#include "Tileselector.h"
#include "UI_info.h"

class Game
{
private:

    void Initialize();
    void Update();
    void Render();

    sf::Vector2u windowSize{1920, 1080};
    sf::String windowTitle{"SFLM Game class"};
    sf::RenderWindow window{};
    static constexpr unsigned short framerateLimit = 120;

    Camera camera{windowSize};
    Tilemap map;
    Tileselector tileselector;
    UI_info coordinatesUI;

    float deltaTime;
    sf::Clock dtClock;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2i mousePosView;
    sf::Vector2i mousePosGrid;
    void updateMousePositions();

public:
    Game();
    void Run();

};

#endif //GAME_H
