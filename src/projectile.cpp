#include "projectile.hpp"
#include <cmath>

Projectile::Projectile(sf::Texture &projectileTexture, const  Spaceship *s)
    : angle{0.f} {

        sprite.setTexture(projectileTexture);
        sprite.setTextureRect(sf::IntRect(0, 0, 2243, 2195));
        sprite.setScale(0.005f, 0.005f);

        // set position and angle values equal to the spaceship's current values.
        x = s->getSprite().getPosition().x;
        y = s->getSprite().getPosition().y;
        angle = s->getAngle();
        radialSize = 4.f;
}


void Projectile::updatePosition() {    
    x += 12*cos(angle * M_PI / 180);
    y += 12*sin(angle * M_PI / 180);

    sprite.setPosition(x, y);

    // set active state to false if the object goes outside the screen.
    if (x < 0 || x > screenWidth || y < 0 || y > screenHeight)
        active = false;
}