#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <SFML/Graphics.hpp>

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

        sf::RenderWindow window;
        sf::Texture texture;
        sf::Sprite player;
        sf::Font font;
        sf::Text statisticsText;
        sf::Time statisticsUpdateTime;

        std::size_t statisticsNumFrames;
        bool isMovingUp;
        bool isMovingDown;
        bool isMovingRight;
        bool isMovingLeft;
};

#endif
