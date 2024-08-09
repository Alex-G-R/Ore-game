#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Tile.h"

class Tilemap {
private:
    sf::Texture tilesetTexture;
    void setTileId(Tile& tile);

public:
    std::vector<std::vector<Tile>> tileMap;

    float tileSizeF = 50.f;
    unsigned tileSize = static_cast<unsigned>(tileSizeF);
    int mapSize = 100;
    int gridWidth = mapSize;
    int gridHeight = mapSize;

    bool isLeftMouseButtonHeld = false;
    bool isRightMouseButtonHeld = false;
    bool isMiddleMouseButtonHeld = false;

    // Load method to initialize the tilemap
    bool load(const std::string& tilesetFilename);

    void SaveLevelToFile(const std::string& filename);
    void loadLevelFromFile(const std::string& filename);
    void subtractOre(sf::Vector2i& mousePosGrid, Tilemap& map);
    void addOre(sf::Vector2i& mousePosGrid, Tilemap& map);
    void changeOreType(sf::Vector2i& mousePosGrid, Tilemap& map);
    void update(Tilemap& map);
    void resetTiles(Tilemap& map);

    // Render method to draw tiles
    void render(sf::RenderWindow& window, int fromX, int toX, int fromY, int toY);
};

#endif // TILEMAP_H
