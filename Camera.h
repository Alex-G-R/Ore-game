
#ifndef CAMERA_H
#define CAMERA_H

#include <Graphics.hpp>

class Camera {
public:
    Camera(const sf::Vector2u& windowSize);
    void Update(float& deltaTime);
    sf::View getView();

private:
    float viewSpeed = 200.f;
    sf::View view;
};



#endif //CAMERA_H
