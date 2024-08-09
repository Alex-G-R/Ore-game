
#include "Tileselector.h"

Tileselector::Tileselector()
{
    selector.setSize(sf::Vector2f(50.f, 50.f));
    selector.setPosition(100.f, 100.f);
    selector.setFillColor(sf::Color::Transparent);
    selector.setOutlineThickness(2.f);
    selector.setOutlineColor(sf::Color::Red);
}

void Tileselector::Update(sf::Vector2i& mousePosGrid, Tilemap& map)
{
    selector.setPosition(static_cast<float>(mousePosGrid.x) * map.tileSizeF, static_cast<float>(mousePosGrid.y) * map.tileSizeF);
}

void Tileselector::Render(sf::RenderWindow& window)
{
    window.draw(selector);
}