#include "Game.hpp"
#include "StringHelpers.hpp"

#define WIDTH 1280
#define HEIGH 720

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: window(sf::VideoMode(WIDTH, HEIGH), "Minusculo")
, texture()
, player()
, font()
, statisticsText()
, statisticsUpdateTime()
, statisticsNumFrames(0)
, isMovingUp(false)
, isMovingDown(false)
, isMovingLeft(false)
, isMovingRight(false) {

    if (!texture.loadFromFile("resources/bee.png")) {
        // Handle texture loading error...
    }

    player.setTexture(texture);
    player.setPosition(WIDTH / 2, HEIGH / 2);

    font.loadFromFile("resources/LinBiolinum_R.otf");
    statisticsText.setFont(font);
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

            processEvents();
            update(TimePerFrame);
        }

        updateStatistics(elapsedTime);
        render();
    }
}

void Game::processEvents() {

    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                window.close();
                break;
        }
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(sf::Time deltaTime) {

    sf::Vector2f movement(0.f, 0.f);
    if (isMovingUp)
        movement.y -= PlayerSpeed;
    if (isMovingDown)
        movement.y += PlayerSpeed;
    if (isMovingLeft)
        movement.x -= PlayerSpeed;
    if (isMovingRight)
        movement.x += PlayerSpeed;

    player.move(movement * deltaTime.asSeconds());
}

void Game::render() {

    window.clear();
    window.draw(player);
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

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {

    if (key == sf::Keyboard::R)
        player.setPosition(WIDTH / 2, HEIGH /2);

    if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
        isMovingUp = isPressed;
    else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
        isMovingDown = isPressed;
    else if (key == sf::Keyboard::A || key == sf::Keyboard::Left)
        isMovingLeft = isPressed;
    else if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
        isMovingRight = isPressed;
}

