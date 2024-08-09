
#ifndef CAMERA_H
#define CAMERA_H

#include <Graphics.hpp>

class Camera {
public:
    Camera(const sf::Vector2u& windowSize);
    void Update(float& deltaTime);
    void updateRenderDistance(float tileSizeF, int mapSize);
    sf::View getView();

    int fromX = 0;
    int toX = 0;
    int fromY = 0;
    int toY = 0;

private:
    float viewSpeed = 200.f;
    sf::View view;
};



#endif //CAMERA_H
