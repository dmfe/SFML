#ifndef __INSECT_HPP__
#define __INSECT_HPP__

#include "Entity.hpp"
#include "ResourceIndentifiers.hpp"

class Insect : public Entity {

  public:
    enum Type {
      Ladybug,
      Fly,
      Bee,
    };

  public:
    explicit Insect(Type type, const TextureHolder &textures);

  private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  private:
    Type type;
    sf::Sprite sprite;
};

#endif
