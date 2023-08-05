#include "game_object.hpp"


GameObject::GameObject()
    : active{true}, x{0.f}, y{0.f}, radialSize{0.f} {
}


bool GameObject::getActive() const {
    return active;
}


bool GameObject::hasCollidedWith(GameObject *object) {
    // get position and size of the current object
    float x1 = this->getSprite().getPosition().x;
    float y1 = this->getSprite().getPosition().y;
    float r1 = this->getSize();

    // get position and size of the other object.
    float x2 = object->getSprite().getPosition().x;
    float y2 = object->getSprite().getPosition().y;
    float r2 = object->getSize();

    float squaredCurrentDistance = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
    float squaredCriticalDistance = (r1 + r2)*(r1 + r2);

    // collision occurs when squaredCurrentDistance is not greater than squaredCriticalDistance.
    return squaredCurrentDistance <= squaredCriticalDistance;
}


float GameObject::getSize() const {
    return radialSize;
}


sf::Sprite GameObject::getSprite() const {
    return sprite;
}


void GameObject::setActive(bool val) {
    active = val;
}