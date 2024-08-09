
#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"


class Tile {
public:
    Tile() : shape(sf::Vector2f(0, 0)) {}

    int tileID;

    /* Ore type */
    // -> Coal = 0
    // -> Gold = 1
    int oreType;

    int oreAmount;

    sf::RectangleShape shape;
};



#endif //TILE_H
