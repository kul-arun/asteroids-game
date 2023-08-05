#include "spaceship.hpp"
#include <cmath>


Spaceship::Spaceship(sf::Texture &spaceshipTexture)
    : thrust{false}, angle{0.f} {

        sprite.setTexture(spaceshipTexture);
        sprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
        sprite.setOrigin(500, 500);
        sprite.setScale(0.03, 0.03);
        
        // centre the spaceship.
        x = (screenWidth - sprite.getGlobalBounds().width) / 2.f;
        y = (screenHeight - sprite.getGlobalBounds().height) / 2.f;
        radialSize = 13.f;
}


float Spaceship::getAngle() const {
    return angle;
}


void Spaceship::rotate(float val, std::string dir) {
    if (dir == "clockwise")
        angle += val;
    if (dir == "anticlockwise")
        angle -= val;
}


void Spaceship::setThrust(bool val) {
    thrust = val;
}   


void Spaceship::updatePosition() {
    static float dx{0.f}, dy{0.f};

    if (thrust) {
        dx += 0.1 * cos(angle * M_PI / 180);
        dy += 0.1 * sin(angle * M_PI / 180);
    }

    // slow down movement when there is no thrust.
    else {
        dx *= 0.98;
        dy *= 0.98;
    }

    // limit the maximum speed of spaceship.
    float maxDistance = 7.f;
    float distance = sqrt(dx*dx + dy*dy);

    if (distance > maxDistance) {
        dx *= maxDistance/distance;
        dy *= maxDistance/distance;
    }

    x += dx;
    y += dy;

    // wrap around the screen borders.
    if (x > screenWidth)
        x = 0;

    if (x < 0)
        x = screenWidth;
    
    if (y > screenHeight)
        y = 0;
    
    if (y < 0)
        y = screenHeight;
    
    sprite.setPosition(x, y);
    sprite.setRotation(angle + 90);
}