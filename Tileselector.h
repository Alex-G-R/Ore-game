
#ifndef TILESELECTOR_H
#define TILESELECTOR_H

#include <SFML/Graphics.hpp>
#include "Tilemap.h"

class Tileselector {
public:
    Tileselector();
    void Update(sf::Vector2i& mousePosGrid, Tilemap& map);
    void Render(sf::RenderWindow& window);

private:
    sf::RectangleShape selector;
};



#endif //TILESELECTOR_H
