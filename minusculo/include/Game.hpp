#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"

#define WIDTH 1280
#define HEIGH 720

class Game : private sf::NonCopyable {
    public:
        Game();
        void run();

    private:
        void processEvents();
        void update(sf::Time deltaTime);
        void render();

        void updateStatistics(sf::Time elapsedTime);
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    private:
        static const float PlayerSpeed;
        static const sf::Time TimePerFrame;

        ResourceHolder<sf::Texture, Textures::ID> textures;
        ResourceHolder<sf::Font, Fonts::ID> fonts;

        sf::RenderWindow window;
        sf::Sprite player;
        sf::Sprite landscape;
        sf::Text statisticsText;
        sf::Time statisticsUpdateTime;

        std::size_t statisticsNumFrames;
        bool isMovingUp;
        bool isMovingDown;
        bool isMovingRight;
        bool isMovingLeft;
};

#endif
