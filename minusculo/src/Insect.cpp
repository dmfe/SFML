#include "Insect.hpp"
#include "ResourceHolder.hpp"

Textures::ID toTextureID(Insect::Type type) {
  switch (type) {
  case Insect::Ladybug:
    return Textures::Ladybug;
  case Insect::Bee:
    return Textures::Bee;
  case Insect::Fly:
    return Textures::Fly;
  default:
    return Textures::Ladybug;
  }
}

Insect::Insect(Type type, const TextureHolder &textures)
: type(type)
, sprite(textures.get(toTextureID(type))) {

  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Insect::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {

  target.draw(sprite, states);
}

