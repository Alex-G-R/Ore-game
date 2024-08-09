
#ifndef UI_INFO_H
#define UI_INFO_H

#include <SFML/Graphics.hpp>
#include <sstream>

class UI_info {
public:
    sf::Font font;
    sf::Text text;

    void initText();
    void updateText(sf::Vector2i& mousePosScreen, sf::Vector2i& mousePosWindow, sf::Vector2i& mousePosView, sf::Vector2i& mousePosGrid);
    void Render(sf::RenderWindow& window);
};



#endif //UI_INFO_H
