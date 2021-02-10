#ifndef __INSECT_HPP__
#define __INSECT_HPP__

#include "Entity.hpp"

class Insect : public Entity {

    public:
        enum Type {
            Ladybug,
            Fly,
            Bee,
        };

    public:
        explicit Insect(Type type);

    private:
        Type type;
};

#endif

