#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Tilemap {
private:
    std::vector<std::vector<sf::RectangleShape>> tileMap;
    sf::Texture tilesetTexture;
public:
    // Load method to initialize the tilemap
    bool load(const std::string& tilesetFilename, const sf::Vector2u& tileSize, const std::vector<int>& level, unsigned int gridWidth, unsigned int gridHeight);

    // Render method to draw tiles
    void render(sf::RenderWindow& window, int fromX, int toX, int fromY, int toY);

    // Other necessary methods
};

#endif // TILEMAP_H
