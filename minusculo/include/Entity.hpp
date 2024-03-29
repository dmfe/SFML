#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <SFML/Graphics.hpp>

#include "SceneNode.hpp"

class Entity : public SceneNode {

    public:
        void setVelocity(sf::Vector2f velocity);
        void setVelocity(float vx, float vy);
        void accelerate(sf::Vector2f velocity);
        void accelerate(float vx, float vy);
        sf::Vector2f getVelocity() const;

    private:
        virtual void updateCurrent(sf::Time dt);

    private:
        sf::Vector2f velocity;
};

#endif
