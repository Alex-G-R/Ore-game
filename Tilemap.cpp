#include "Tilemap.h"
#include <iostream>
#include <SFML/Graphics.hpp>

struct Tile_bin {
    int tileID;         // 4 bytes
    int oreType;     // 4 bytes
    int oreAmount;     // 4 bytes
    float posX;         // 4 bytes
    float posY;         // 4 bytes
    float sizeWidth;    // 4 bytes
    float sizeHeight;   // 4 bytes
};


Tile ConvertToTile(const Tile_bin& tile_bin) {
    Tile tile;
    tile.tileID = tile_bin.tileID;
    tile.oreType = tile_bin.oreType;
    tile.oreAmount = tile_bin.oreAmount;
    tile.shape.setPosition(tile_bin.posX, tile_bin.posY);
    tile.shape.setSize(sf::Vector2f(tile_bin.sizeWidth, tile_bin.sizeHeight));
    return tile;
}

Tile_bin ConvertToTileBin(const Tile& tile) {
    Tile_bin tile_bin;
    tile_bin.tileID = tile.tileID;
    tile_bin.oreType = tile.oreType;
    tile_bin.oreAmount = tile.oreAmount;
    tile_bin.posX = tile.shape.getPosition().x;
    tile_bin.posY = tile.shape.getPosition().y;
    tile_bin.sizeWidth = tile.shape.getSize().x;
    tile_bin.sizeHeight = tile.shape.getSize().y;
    return tile_bin;
}

bool Tilemap::load(const std::string& tilesetFilename) {
    // Load the tileset texture from the file
    if (!tilesetTexture.loadFromFile(tilesetFilename)) {
        std::cerr << "Error loading tileset texture: " << tilesetFilename << std::endl;
        return false;
    }

    // Initialize the tileMap with tiles from the tileset
    for (unsigned int y = 0; y < gridHeight; ++y) {
        for (unsigned int x = 0; x < gridWidth; ++x) {
            Tile& tile = tileMap[x][y];

            tile.shape.setSize(sf::Vector2f(tileSize, tileSize));
            tile.shape.setPosition(x * tileSize, y * tileSize);
            tile.shape.setTexture(&tilesetTexture);

            // Set TileID based on Coal amount
            if(tile.oreAmount >= 10)
            {
                if(tile.oreType == 0)
                {
                    tile.tileID = 5;
                }
                else if(tile.oreType == 1)
                {
                    tile.tileID = 10;
                }
            }
            else if(tile.oreAmount >= 8)
            {
                if(tile.oreType == 0)
                {
                    tile.tileID = 4;
                }
                else if(tile.oreType == 1)
                {
                    tile.tileID = 9;
                }
            }
            else if(tile.oreAmount >= 6)
            {
                if(tile.oreType == 0)
                {
                    tile.tileID = 3;
                }
                else if(tile.oreType == 1)
                {
                    tile.tileID = 8;
                }
            }
            else if (tile.oreAmount >= 3)
            {
                if(tile.oreType == 0)
                {
                    tile.tileID = 2;
                }
                else if(tile.oreType == 1)
                {
                    tile.tileID = 7;
                }
            }
            else if(tile.oreAmount >= 1)
            {
                if(tile.oreType == 0)
                {
                    tile.tileID = 1;
                }
                else if(tile.oreType == 1)
                {
                    tile.tileID = 6;
                }
            }
            else
            {
                tile.tileID = 0;
            }

            // Set the texture rectangle based on the tileID
            if (tile.tileID >= 0) {
                sf::IntRect textureRect(tile.tileID * tileSize, 0, tileSize, tileSize);
                tile.shape.setTextureRect(textureRect);
            } else {
                tile.shape.setTextureRect(sf::IntRect(0, 0, tileSize, tileSize)); // Default texture rectangle if ID is invalid
            }
        }
    }

    return true;
}

void Tilemap::render(sf::RenderWindow& window, int fromX, int toX, int fromY, int toY) {
    // go over the specified range and draw tiles
    for (int x = fromX; x < toX; x++) {
        for (int y = fromY; y < toY; y++) {
            sf::RectangleShape& tileShape = tileMap[x][y].shape;
            window.draw(tileShape);
        }
    }
}

void Tilemap::SaveLevelToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    for (int i = 0; i < gridHeight; ++i) {
        for (int j = 0; j < gridWidth; ++j) {
            const Tile& tile = tileMap[i][j];
            Tile_bin tile_bin = ConvertToTileBin(tile);
            file.write(reinterpret_cast<const char*>(&tile_bin), sizeof(Tile_bin));
        }
    }

    if (!file.good()) {
        throw std::runtime_error("Error writing to file " + filename);
    }

    file.close();
}

void Tilemap::loadLevelFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    tileMap.resize(gridHeight, std::vector<Tile>(gridWidth));
    for (int i = 0; i < gridHeight; ++i) {
        for (int j = 0; j < gridWidth; ++j) {
            Tile_bin tile_bin;
            file.read(reinterpret_cast<char*>(&tile_bin), sizeof(Tile_bin));
            if (!file) {
                throw std::runtime_error("Error reading from file " + filename);
            }
            tileMap[i][j] = ConvertToTile(tile_bin);
        }
    }

    file.close();
}

void Tilemap::addOre(sf::Vector2i& mousePosGrid, Tilemap& map)
{
    if (!isLeftMouseButtonHeld) // If the mouse button was not held in the previous frame
    {
        isLeftMouseButtonHeld = true;

        // Ensure the grid position is within bounds
        if (mousePosGrid.x >= 0 && mousePosGrid.x < gridWidth &&
            mousePosGrid.y >= 0 && mousePosGrid.y < gridHeight)
        {
            Tile& tile = tileMap[mousePosGrid.x][mousePosGrid.y]; // Access the tile in the map

            tile.oreAmount++;

            if (!map.load("assets/tilemap.png"))
                throw std::runtime_error("Cannot load tileset.png");
        }
    }
}

void Tilemap::subtractOre(sf::Vector2i& mousePosGrid, Tilemap& map)
{
    if (!isRightMouseButtonHeld) // If the mouse button was not held in the previous frame
    {
        isRightMouseButtonHeld = true;

        // Ensure the grid position is within bounds
        if (mousePosGrid.x >= 0 && mousePosGrid.x < gridWidth &&
            mousePosGrid.y >= 0 && mousePosGrid.y < gridHeight)
        {
            Tile& tile = tileMap[mousePosGrid.x][mousePosGrid.y]; // Access the tile in the map

            if(tile.oreAmount >= 1)
                tile.oreAmount--;

            if (!map.load("assets/tilemap.png"))
                throw std::runtime_error("Cannot load tileset.png");
        }
    }
}

void Tilemap::changeOreType(sf::Vector2i& mousePosGrid, Tilemap& map)
{
    if (!isMiddleMouseButtonHeld) // If the mouse button was not held in the previous frame
    {
        isMiddleMouseButtonHeld = true;

        // Ensure the grid position is within bounds
        if (mousePosGrid.x >= 0 && mousePosGrid.x < gridWidth &&
            mousePosGrid.y >= 0 && mousePosGrid.y < gridHeight)
        {
            Tile& tile = tileMap[mousePosGrid.x][mousePosGrid.y]; // Access the tile in the map

            if(tile.oreType == 0)
            {
                tile.oreType = 1;
            }
            else
            {
                tile.oreType = 0;
            }

            if (!map.load("assets/tilemap.png"))
                throw std::runtime_error("Cannot load tileset.png");
        }
    }
}

void Tilemap::resetTiles(Tilemap& map)
{
    for (int i = 0; i < gridHeight; ++i)
    {
        for (int j = 0; j < gridWidth; ++j)
        {
            tileMap[i][j].oreAmount = 0; // Reset each tileID in the map to 0
        }
    }

    if (!map.load("assets/tilemap.png"))
        throw std::runtime_error("Cannot load tileset.png");
}