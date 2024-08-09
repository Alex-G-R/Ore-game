
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

class Game
{
private:

    void Initialize();
    void Update();
    void Render();

    void initializeTileMap(const std::string& tilesetFilename, const sf::Vector2u& tileSize, std::vector<std::vector<sf::RectangleShape>>& tileMap, unsigned int gridWidth, unsigned int gridHeight);
    void SaveLevelToFile(const std::string& filename, const std::vector<int>& level, int gridWidth, int gridHeight);



    int mapSize = 100;
    int gridWidth = mapSize;
    int gridHeight = mapSize;

    sf::Vector2u windowSize{1920, 1080};
    sf::String windowTitle{"SFLM Game class"};
    sf::RenderWindow window{};
    static constexpr unsigned short framerateLimit = 120;

    Camera camera{windowSize};
    Tilemap map;
    std::vector<int> level;
    void loadLevelFromFile(const std::string& filename, std::vector<int>& level, int& gridWidth, int& gridHeight);

    void changeTile();

    float tileSizeF = 50.f;
    unsigned tileSize = static_cast<unsigned>(tileSizeF);

    int fromX = 0;
    int toX = 0;
    int fromY = 0;
    int toY = 0;


    float deltaTime;
    sf::Clock dtClock;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2i mousePosView;
    sf::Vector2i mousePosGrid;
    void updateMousePositions();
    void updateMouseInfoUI();

    sf::Font font;
    sf::Text text;

    sf::RectangleShape tileSelector;

    bool isLeftMouseButtonHeld = false;

public:
    Game();
    void Run();

};

#endif //GAME_H
