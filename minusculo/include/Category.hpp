#ifndef __CATEGORY_HPP__
#define __CATEGORY_HPP__

namespace Category {
    enum Type {
        None = 0,
        Scene = 1 << 0,
        PlayerInsect = 1 << 1,
        AlliedInsect = 1 << 2,
        EnemyInsect = 1 << 3,
    };
}

#endif