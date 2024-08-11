
#include "UI_info.h"

void UI_info::initText()
{
    font.loadFromFile("Fonts/nulshock.otf");

    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setPosition(20.f, 20.f);
    text.setString("TEST");
}

void UI_info::updateText(sf::Vector2i& mousePosScreen, sf::Vector2i& mousePosWindow, sf::Vector2i& mousePosView, sf::Vector2i& mousePosGrid, std::vector<std::vector<Tile>>& tileMap, int& mapSize)
{
    Tile& tile = tileMap[mousePosGrid.x][mousePosGrid.y];
    std::stringstream ss;
    ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
        << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
        << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
        << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n \n";
    // Check if in bounds
    if (mousePosGrid.x >= 0 && mousePosGrid.x < mapSize && mousePosGrid.y >= 0 && mousePosGrid.y < mapSize)
    {
        ss << "Texture_ID: " << tile.tileID << "\n"
        << "Ore type: " << tile.oreType << "\n"
        << "Ore amount: " << tile.oreAmount << "\n";
    }

    text.setPosition(20.f, 20.f);
    text.setCharacterSize(36);
    text.setString(ss.str());
}

void UI_info::displayControls(sf::RenderWindow& window)
{

    std::stringstream ss;
    // Add info about controls
    ss << "Middle mouse button: add / change ore type \n"
    << "Left mouse button: increment ore amount by 1 \n"
    << "Right mouse button: decrement ore amount by 1 \n"
    << "R: Reset map \n";

    text.setPosition(20.f, window.getSize().y - 130.f);
    text.setCharacterSize(24);
    text.setString(ss.str());

    Render(window);
}

void UI_info::Render(sf::RenderWindow& window)
{
    window.draw(text);
}

