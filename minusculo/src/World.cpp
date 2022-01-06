#include <SFML/Graphics/RenderWindow.hpp>

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

  // Scroll the world
  worldView.move(0.f, scrollSpeed * dt.asSeconds());

  // Move the player sidewards (insect scouts follow the leader insect)
  sf::Vector2f position = playerInsect->getPosition();
  sf::Vector2f velocity = playerInsect->getVelocity();

  // If the player touches borders, flip its X velocity
  if (position.x <= worldBounds.left + 150.f
      || position.x >= worldBounds.left + worldBounds.width -150.f) {

    velocity.x = -velocity.x;
    playerInsect->setVelocity(velocity);
  }

  sceneGraph.update(dt);
}

void World::draw() {
  window.setView(worldView);
  window.draw(sceneGraph);
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
  std::unique_ptr<Insect> leader(new Insect(Insect::Bee, textures));
  playerInsect = leader.get();
  playerInsect->setPosition(spawnPosition);
  playerInsect->setVelocity(40.f, scrollSpeed);
  sceneLayers[Air]->attachChild(std::move(leader));

  // Add two escorting insects, placed relatively to the leader insect
  std::unique_ptr<Insect> leftEscort(new Insect(Insect::Ladybug, textures));
  leftEscort->setPosition(-90.f, 60.f);
  playerInsect->attachChild(std::move(leftEscort));

  std::unique_ptr<Insect> rightEscort(new Insect(Insect::Ladybug, textures));
  rightEscort->setPosition(90.f, 60.f);
  playerInsect->attachChild(std::move(rightEscort));
}

