#ifndef __SNIPPETS_HPP__
#define __SNIPPETS_HPP__

#include <string>
#include <random>
#include "cocos2d.h"
#include "json.hpp"

namespace snippets {

    inline void loadJSON(const std::string& path, nlohmann::json& j) {
        auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(path);
        j = nlohmann::json::parse(std::string((char*)fileData.getBytes(), (size_t)fileData.getSize()));
    }

    inline int randomInteger(int min, int max) {
        static std::random_device          rd;
        static std::default_random_engine  e1(rd());
        std::uniform_int_distribution<int> uniform_dist(min, max);
        return uniform_dist(e1);
    }
}

#endif