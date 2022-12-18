#include <map>
#include <string>
#include <algorithm>

#include "Player.hpp"
#include "CommandQueue.hpp"
#include "Insect.hpp"
#include "Foreach.hpp"

struct InsectMover {
    InsectMover(float vx, float vy)
    : velocity(vx, vy)
    {}

    void operator() (Insect& insect, sf::Time) const {
        insect.accelerate(velocity);
    }

    sf::Vector2f velocity;
};

Player::Player() {
    // Set initial key bindings
    keyBindings[sf::Keyboard::Left] = MoveLeft;
    keyBindings[sf::Keyboard::Right] = MoveRight;
    keyBindings[sf::Keyboard::Up] = MoveUp;
    keyBindings[sf::Keyboard::Down] = MoveDown;

    // Set initial action bindings
    initializeActions();

    // Assign all categories to player's insect
    FOREACH(auto& pair, actionBindings)
        pair.second.category = Category::PlayerInsect;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
    if (event.type == sf::Event::KeyPressed) {
        // Check if pressed key appears in key binding, trigger command if so
        auto found = keyBindings.find(event.key.code);
        if (found != keyBindings.end() && !isRealtimeAction(found->second))
            commands.push(actionBindings[found->second]);
    }
}

void Player::handleRealtimeInput(CommandQueue& commands) {
    // Traverse all assigned keys and check if they are pressed
    FOREACH(auto pair, keyBindings) {
        // If key is pressed, lookup action and trigger corresponding command
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
            commands.push(actionBindings[pair.second]);
    }
}

void Player::assignKey(Action action, sf::Keyboard::Key key) {
    // Remove all keys that already map to action
    for (auto itr = keyBindings.begin(); itr != keyBindings.end();) {
        if (itr->second == action)
            keyBindings.erase(itr++);
        else
            ++itr;

        // Insert new binding
        keyBindings[key] = action;
    }
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const {
    FOREACH(auto pair, keyBindings) {
        if (pair.second == action)
            return pair.first;
    }

    return sf::Keyboard::Unknown;
}

void Player::initializeActions() {
    const float playerSpeed = 200.f;

    actionBindings[MoveLeft].action = derivedAction<Insect>(InsectMover(-playerSpeed, 0.f));
    actionBindings[MoveRight].action = derivedAction<Insect>(InsectMover(+playerSpeed, 0.f));
    actionBindings[MoveUp].action = derivedAction<Insect>(InsectMover(0.f, -playerSpeed));
    actionBindings[MoveDown].action = derivedAction<Insect>(InsectMover(0.f, +playerSpeed));
}

bool Player::isRealtimeAction(Action action) {
    switch (action)
    {
        case MoveLeft:
        case MoveRight:
        case MoveDown:
        case MoveUp:
            return true;
        
        default:
            return false;
    }
}
