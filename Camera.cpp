
#include "Camera.h"

Camera::Camera(const sf::Vector2u& windowSize)
{
    view.setSize(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
    view.setCenter(static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f);
}

void Camera::Update(float& deltaTime)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // Left
    {
        view.move(-viewSpeed * deltaTime, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // Right
    {
        view.move(viewSpeed * deltaTime, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // Up
    {
        view.move(0.f, -viewSpeed * deltaTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // Down
    {
        view.move(0.f, viewSpeed * deltaTime);
    }
}

void Camera::updateRenderDistance(float tileSizeF, int mapSize)
{
    fromY = view.getCenter().y / tileSizeF - 9;
    toY =  view.getCenter().y / tileSizeF + 11;

    fromX = view.getCenter().x / tileSizeF - 9;
    toX = view.getCenter().x / tileSizeF + 11;

    if(fromX < 0)
        fromX = 0;
    else if (fromX >= mapSize)
        fromX = mapSize - 1;
    if(toX < 0)
        toX = 0;
    else if (toX >= mapSize)
        toX = mapSize - 1;

    if(fromY < 0)
        fromY = 0;
    else if (fromY >= mapSize)
        fromY = mapSize - 1;
    if(fromX < 0)
        fromX = 0;
    else if (fromX >= mapSize)
        fromX = mapSize - 1;
}


sf::View Camera::getView()
{
    return view;
}