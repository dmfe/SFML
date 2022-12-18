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
: Insect::Insect(type, textures, false) {}

Insect::Insect(Type type, const TextureHolder &textures, bool isPlayer)
: type(type)
, sprite(textures.get(toTextureID(type)))
, isPlayer(isPlayer) {

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

sf::FloatRect Insect::getSpriteBounds() {
    return sprite.getLocalBounds();
}

unsigned int Insect::getCategory() const {
    if (isPlayer)
        return Category::PlayerInsect;

    switch (type)
    {
        case Bee:
            return Category::AlliedInsect;
        default:
            return Category::EnemyInsect;
    }
}

void Insect::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}
