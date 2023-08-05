#pragma once


#include "game_object.hpp"


class Asteroid : public GameObject {
    private:
        // category denotes the category of the object. Asteroid objects
        // are split into two categories on the basis of their motion.
        bool category;

    public:
        Asteroid(sf::Texture &);
        void updatePosition();
};