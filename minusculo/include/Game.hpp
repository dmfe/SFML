#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceHolder.hpp"
#include "ResourceIndentifiers.hpp"
#include "World.hpp"

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
    static const sf::Time TimePerFrame;

    FontHolder fonts;

    sf::RenderWindow window;
    World world;

    sf::Text statisticsText;
    sf::Time statisticsUpdateTime;
    std::size_t statisticsNumFrames;
};

#endif
