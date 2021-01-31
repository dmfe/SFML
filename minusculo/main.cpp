#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    sf::Texture texture;
    if (!texture.loadFromFile("resources/ladybug.png")) {
        // error...
        std::cerr << "Unable to load textures." << std::endl;
        return 1;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    //sf::CircleShape shape(50.0f);
    //shape.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                sprite.move(-10, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                sprite.move(10, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                sprite.move(0, -10);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                sprite.move(0, 10);
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
