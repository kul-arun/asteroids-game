#pragma once


#include "game_object.hpp"
#include "spaceship.hpp"


class Projectile : public GameObject {
    private:
        float angle;
    
    public:
        Projectile(sf::Texture &, const Spaceship *);
        void updatePosition();
};