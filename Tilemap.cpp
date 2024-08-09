#include "Tilemap.h"
#include <iostream>
#include <SFML/Graphics.hpp>

bool Tilemap::load(const std::string& tilesetFilename, const sf::Vector2u& tileSize,
                   const std::vector<int>& level, unsigned int gridWidth, unsigned int gridHeight) {
    if (!tilesetTexture.loadFromFile(tilesetFilename)) {
        std::cerr << "Error loading tileset texture: " << tilesetFilename << std::endl;
        return false;
    }

    // Resize the tileMap to the grid dimensions
    tileMap.resize(gridHeight, std::vector<sf::RectangleShape>(gridWidth));

    // Initialize the tileMap with tiles from the tileset
    for (unsigned int y = 0; y < gridHeight; ++y) {
        for (unsigned int x = 0; x < gridWidth; ++x) {
            int tileID = level[y * gridWidth + x];
            sf::RectangleShape& tile = tileMap[y][x];
            tile.setSize(sf::Vector2f(tileSize.x, tileSize.y));
            tile.setPosition(x * tileSize.x, y * tileSize.y);
            tile.setTexture(&tilesetTexture);

            // Set the texture rectangle based on the tileID
            if (tileID >= 0) {
                sf::IntRect textureRect(tileID * tileSize.x, 0, tileSize.x, tileSize.y);
                tile.setTextureRect(textureRect);
            } else {
                tile.setTextureRect(sf::IntRect(0, 0, tileSize.x, tileSize.y)); // Default texture rectangle if ID is invalid
            }
        }
    }

    return true;
}

void Tilemap::render(sf::RenderWindow& window, int fromX, int toX, int fromY, int toY) {
    // Iterate over the specified range and draw tiles
    for (int x = fromX; x < toX; x++) {
        for (int y = fromY; y < toY; y++) {
            window.draw(tileMap[y][x]);
        }
    }
}
