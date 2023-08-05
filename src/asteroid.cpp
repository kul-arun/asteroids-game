#include "asteroid.hpp"
#include <random>


Asteroid::Asteroid(sf::Texture &asteroidTexture)
    : category{(rand() % 2) ? true : false} {
        
        sprite.setTexture(asteroidTexture);
        sprite.setTextureRect(sf::IntRect(4*128, 2*128, 128, 128));
        sprite.setOrigin(64, 64);
        sprite.setScale(0.5, 0.5);

        x = rand() % screenWidth;
        y = rand() % screenHeight;
        radialSize = 21.f;
}

void Asteroid::updatePosition() {
    // update position based on the object's category.
    if (category) {
        x += rand() % 2 + 2;
        y -= rand() % 2 + 2;
    }
    else {
        x -= rand() % 2 + 2;
        y += rand() % 2 - 2;
    }

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
    sprite.rotate(5);
}