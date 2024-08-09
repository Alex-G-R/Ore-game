
#include "Player.h"

Player::Player()
{
    shape.setSize(sf::Vector2f(50.f, 50.f));
    shape.setPosition(100.f, 100.f);
    shape.setFillColor(sf::Color::Blue);
}

void Player::Update()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        shape.move(-5.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        shape.move(5.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        shape.move(0.f, -5.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        shape.move(0.f, 5.f);
}

void Player::Render(sf::RenderWindow& window)
{
    window.draw(shape);
}
