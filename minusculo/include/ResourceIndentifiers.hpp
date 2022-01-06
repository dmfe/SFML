#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP

// Forward declaration on SFML classes
namespace sf {
  class Texture;
  class Font;
}

namespace Textures {
  enum ID { GrassLS, Ladybug, Fly, Bee };
}

namespace Fonts {
  enum ID { LinBio };
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif
