#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceIndentifiers.hpp"
#include "World.hpp"
#include "Player.hpp"

#define WIDTH 1280
#define HEIGH 720

class Game : private sf::NonCopyable {

    public:
        Game();
        void run();

    private:
        void processInput();
        void update(sf::Time deltaTime);
        void render();
        void updateStatistics(sf::Time elapsedTime);

    private:
        static const sf::Time TimePerFrame;

        FontHolder fonts;

        sf::RenderWindow window;
        World world;
        Player player;

        sf::Text statisticsText;
        sf::Time statisticsUpdateTime;
        std::size_t statisticsNumFrames;
};

#endif
