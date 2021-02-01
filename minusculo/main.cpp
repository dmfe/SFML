#include <iostream>
#include <SFML/Graphics.hpp>

#define WIDTH 1280
#define HEIGH 720
#define STEP 10.0

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGH), "SFML works!");

    sf::Texture texture;
    if (!texture.loadFromFile("resources/ladybug_small.png")) {
        // error...
        std::cerr << "Unable to load textures." << std::endl;
        return 1;
    }

    uint texture_width = texture.getSize().x;
    uint texture_height = texture.getSize().y;

    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen()) {
        sf::Event event;

        float x = sprite.getPosition().x;
        float y = sprite.getPosition().y;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && x > STEP)
                sprite.move(-STEP, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (x + texture_width) < (WIDTH - STEP))
                sprite.move(STEP, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && y > STEP)
                sprite.move(0, -STEP);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (y + texture_height) < (HEIGH - STEP))
                sprite.move(0, STEP);
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
