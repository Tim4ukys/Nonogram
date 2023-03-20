#ifndef __SNIPPETS_HPP__
#define __SNIPPETS_HPP__

#include <random>

namespace snippets {
    inline int randomInteger(int min, int max) {
        static std::random_device          rd;
        static std::default_random_engine  e1(rd());
        std::uniform_int_distribution<int> uniform_dist(min, max);
        return uniform_dist(e1);
    }
}

#endif