#include "Entity.hpp"

void Entity::setVelocity(sf::Vector2f vel) {
    velocity = vel;
}

void Entity::setVelocity(float vx, float vy) {
    velocity.x = vx;
    velocity.y = vy;
}

void Entity::accelerate(sf::Vector2f vel) {
    velocity += vel;
}

void Entity::accelerate(float vx, float vy) {
    velocity.x += vx;
    velocity.y += vy;
}

sf::Vector2f Entity::getVelocity() const {
    return velocity;
}

void Entity::updateCurrent(sf::Time dt) {
    move(velocity * dt.asSeconds());
}
