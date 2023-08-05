#pragma once


#include <SFML/Graphics.hpp>


const unsigned int screenWidth {1200};
const unsigned int screenHeight {800};


class GameObject {
    protected:
        // active denotes the state of existence of the object.
        bool active;
        // radialSize denotes the approximate radial size of the object.
        float x, y, radialSize;
        sf::Sprite sprite;

    public:
        GameObject();
        bool getActive() const;
        bool hasCollidedWith(GameObject *);
        float getSize() const;
        sf::Sprite getSprite() const;
        void setActive(bool);
};