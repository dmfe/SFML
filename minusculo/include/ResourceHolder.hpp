#ifndef __RESOURCE_HOLDER_HPP__
#define __RESOURCE_HOLDER_HPP__

#include <map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

namespace Textures {
    enum ID { Landscape, Ladybug, Fly, Bee };
}

class TextureHolder {

    public:
        void load(Textures::ID id, const std::string& filename);

        sf::Texture& get(Textures::ID id);
        const sf::Texture& get(Textures::ID id) const;

    private:
        std::map<Textures::ID, std::unique_ptr<sf::Texture>> textureMap;
};

#endif
