#pragma once


#include "game_object.hpp"
#include <string>


class Spaceship : public GameObject {
    private:
        // Forward motion is controlled by thrust.
        bool thrust;
        float angle;
    
    public:
        Spaceship(sf::Texture &);
        float getAngle() const;
        void rotate(float, std::string);
        void setThrust(bool);
        void updatePosition();
};