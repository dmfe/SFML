#include "ResourceHolder.hpp"

void TextureHolder::load(Textures::ID id, const std::string &filename) {

    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    texture->loadFromFile(filename);

    textureMap.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture& TextureHolder::get(Textures::ID id) {

    auto found = textureMap.find(id);
    return *found->second;
}

const sf::Texture& TextureHolder::get(Textures::ID id) const {

    auto found = textureMap.find(id);
    return *found->second;
}
