
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

void UI_info::updateText(sf::Vector2i& mousePosScreen, sf::Vector2i& mousePosWindow, sf::Vector2i& mousePosView, sf::Vector2i& mousePosGrid)
{
    std::stringstream ss;
    ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
        << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
        << "View: " << mousePosView.x << " " << mousePosView.y << "\n"
        << "Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n";

    text.setString(ss.str());
}

void UI_info::Render(sf::RenderWindow& window)
{
    window.draw(text);
}

