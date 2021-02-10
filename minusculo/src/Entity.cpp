#include "Entity.hpp"

void Entity::setVelocity(sf::Vector2f vel) {
    velocity = vel;
}

void Entity::setVelocity(float vx, float vy) {
    velocity.x = vx;
    velocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const {
    return velocity;
}
