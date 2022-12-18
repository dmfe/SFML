#ifndef __COMMAND_QUEUE_HPP__
#define __COMMAND_QUEUE_HPP__

#include <queue>

#include "Command.hpp"

class CommandQueue {
    public:
        void push(const Command& command);
        Command pop();
        bool isEmpty() const;

    private:
        std::queue<Command> queue;
};

#endif
