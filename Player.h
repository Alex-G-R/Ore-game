#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();
    void Update();
    void Render(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
};

#endif // PLAYER_H
