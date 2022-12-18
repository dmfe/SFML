#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <SFML/Window/Event.hpp>

#include <map>

#include "Command.hpp"

class CommandQueue;

class Player {
    public:
        enum Action {
            MoveLeft,
            MoveRight,
            MoveUp,
            MoveDown,
            ActionCount
        };

        public:
            Player();

            void handleEvent(const sf::Event& event, CommandQueue& commands);
            void handleRealtimeInput(CommandQueue& commands);
            void assignKey(Action action, sf::Keyboard::Key key);
            sf::Keyboard::Key getAssignedKey(Action action) const;

        private:
            void initializeActions();
            static bool isRealtimeAction(Action action);

        private:
            std::map<sf::Keyboard::Key, Action> keyBindings;
            std::map<Action, Command> actionBindings;
};

#endif
