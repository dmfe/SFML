#include <SFML/Window/Event.hpp>

#include "Game.hpp"
#include "StringHelpers.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: window(sf::VideoMode(WIDTH, HEIGH), "Minusculo")
, world(window)
, player()
, fonts()
, statisticsText()
, statisticsUpdateTime()
, statisticsNumFrames(0) {

    // Loading fonts.
    fonts.load(Fonts::LinBio, "resources/fonts/LinBiolinum_R.otf");

    statisticsText.setFont(fonts.get(Fonts::LinBio));
    statisticsText.setPosition(5.f, 5.f);
    statisticsText.setCharacterSize(15);
}

void Game::run() {

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen()) {

        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);
        }

        updateStatistics(elapsedTime);
        render();
    }
}

void Game::processInput() {
    CommandQueue& commands = world.getCommandQueue();

    sf::Event event;
    while (window.pollEvent(event)) {
        player.handleEvent(event, commands);

        if (event.type == sf::Event::Closed)
            window.close();
    }

    player.handleRealtimeInput(commands);
}

void Game::update(sf::Time deltaTime) {
  world.update(deltaTime);
}

void Game::render() {

    window.clear();
    world.draw();

    window.setView(window.getDefaultView());
    window.draw(statisticsText);
    window.display();
}

void Game::updateStatistics(sf::Time elapsedTime) {

    statisticsUpdateTime += elapsedTime;
    statisticsNumFrames++;

    if (statisticsUpdateTime >= sf::seconds(1.0f)) {
        statisticsText.setString(
                "Frames/Second = " + toString(statisticsNumFrames) + "\n" +
                "Time/Update = " + toString(statisticsUpdateTime.asMicroseconds() / statisticsNumFrames) + "us");

        statisticsUpdateTime -= sf::seconds(1.0f);
        statisticsNumFrames = 0;
    }
}
