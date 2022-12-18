#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>

#include "World.hpp"

World::World(sf::RenderWindow& window)
: window(window)
, worldView(window.getDefaultView())
, textures()
, sceneGraph()
, sceneLayers()
, worldBounds(0.f, 0.f, worldView.getSize().x, 2000.f)
, spawnPosition(worldView.getSize().x / 2.f, worldBounds.height - worldView.getSize().y / 2.f)
, scrollSpeed(-50.f)
, playerInsect(nullptr) {

    loadTextures();
    buildScene();

    // Prepare the view
    worldView.setCenter(spawnPosition);
}

void World::update(sf::Time dt) {

    // Scroll the world, reset player velocity
    worldView.move(0.f, scrollSpeed * dt.asSeconds());
    playerInsect->setVelocity(0.f, 0.f);

    // Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
    while (!commandQueue.isEmpty())
        sceneGraph.onCommand(commandQueue.pop(), dt);
    adaptPlayerVelocity();

    // Regular update step, adapt position (correct if outside view)
    sceneGraph.update(dt);
    adaptPlayerPosition();
}

void World::draw() {
    window.setView(worldView);
    window.draw(sceneGraph);
}

CommandQueue& World::getCommandQueue() {
    return commandQueue;
}

void World::loadTextures() {
    textures.load(Textures::Ladybug, "resources/textures/ladybug.png");
    textures.load(Textures::Bee, "resources/textures/bee.png");
    textures.load(Textures::Fly, "resources/textures/fly.png");
    textures.load(Textures::GrassLS, "resources/textures/grass_landscape.png");
}

void World::buildScene() {

    // Initialize different layers
    for (std::size_t i = 0; i < LayerCount; i++) {
        SceneNode::Ptr layer(new SceneNode());
        sceneLayers[i] = layer.get();

        sceneGraph.attachChild(std::move(layer));
    }

    // Prepare the tiled background
    sf::Texture& texture = textures.get(Textures::GrassLS);
    sf::IntRect textureRect(worldBounds);
    texture.setRepeated(true);

    // Add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgourdSprite(new SpriteNode(texture, textureRect));
    backgourdSprite->setPosition(worldBounds.left, worldBounds.top);
    sceneLayers[Background]->attachChild(std::move(backgourdSprite));

    // Add player's insect
    std::unique_ptr<Insect> leader(new Insect(Insect::Ladybug, textures, true));
    playerInsect = leader.get();
    playerInsect->setPosition(spawnPosition);
    playerInsect->setVelocity(40.f, scrollSpeed);
    sceneLayers[Air]->attachChild(std::move(leader));

    // Add two escorting insects, placed relatively to the leader insect
    // std::unique_ptr<Insect> leftEscort(new Insect(Insect::Bee, textures));
    // leftEscort->setPosition(-90.f, 60.f);
    // playerInsect->attachChild(std::move(leftEscort));

    // std::unique_ptr<Insect> rightEscort(new Insect(Insect::Bee, textures));
    // rightEscort->setPosition(90.f, 60.f);
    // playerInsect->attachChild(std::move(rightEscort));
}

void World::adaptPlayerPosition() {
    sf::FloatRect viewBounds(worldView.getCenter() - worldView.getSize() / 2.f,
                             worldView.getSize());
    const float xBorderDistance = playerInsect->getSpriteBounds().width / 2.f;
    const float yBorderDistance = playerInsect->getSpriteBounds().height / 2.f;

    sf::Vector2f position = playerInsect->getPosition();
    position.x = std::max(position.x, viewBounds.left + xBorderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - xBorderDistance);
    position.y = std::max(position.y, viewBounds.top + yBorderDistance);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - yBorderDistance);

    playerInsect->setPosition(position);
}

void World::adaptPlayerVelocity() {
    sf::Vector2f velocity = playerInsect->getVelocity();

    // If moving diagonally, reduce volocity (to have always same velocity)
    if (velocity.x != 0 && velocity.y != 0)
        playerInsect->setVelocity(velocity / std::sqrt(2.f));

    // Add scrolling velocity
    playerInsect->accelerate(0.f, scrollSpeed);
}
