
#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"


class Tile {
public:
    Tile() : shape(sf::Vector2f(0, 0)) {}

    int tileID;

    /* Ore type */
    // -> None = 0;
    // -> Coal = 1
    // -> Gold = 2
    // -> Diamonds = 3
    // -> Iron = 4
    int oreType;

    int oreAmount;

    sf::RectangleShape shape;
};



#endif //TILE_H
