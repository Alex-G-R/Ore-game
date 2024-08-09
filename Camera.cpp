
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

sf::View Camera::getView()
{
    return view;
}