#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ResourceHolder.hpp"
#include "ResourceIndentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Insect.hpp"
#include "CommandQueue.hpp"
#include "Command.hpp"

// Forward declaration
namespace sf {
    class RenderWindow;
}

class World : private sf::NonCopyable {

    public:
        explicit World(sf::RenderWindow& window);
        void update(sf::Time dt);
        void draw();
        CommandQueue& getCommandQueue();

    private:
        void loadTextures();
        void buildScene();
        void adaptPlayerPosition();
        void adaptPlayerVelocity();

    private:
        enum Layer {
            Background,
            Air,
            LayerCount
        };

    private:
        sf::RenderWindow& window;
        sf::View worldView;
        TextureHolder textures;

        SceneNode sceneGraph;
        std::array<SceneNode*, LayerCount> sceneLayers;
        CommandQueue commandQueue;

        sf::FloatRect worldBounds;
        sf::Vector2f spawnPosition;
        float scrollSpeed;
        Insect* playerInsect;
};

#endif
