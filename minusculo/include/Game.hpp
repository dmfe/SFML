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

        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    private:
        static const float PlayerSpeed;
        static const sf::Time TimePerFrame;

        sf::RenderWindow window;
        sf::Texture texture;
        sf::Sprite player;

        bool isMovingUp;
        bool isMovingDown;
        bool isMovingRight;
        bool isMovingLeft;
};

#endif
