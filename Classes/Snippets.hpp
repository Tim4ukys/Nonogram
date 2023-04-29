#ifndef __SNIPPETS_HPP__
#define __SNIPPETS_HPP__

#include <string>
#include <random>
#include <regex>
#include "cocos2d.h"
#include "json.hpp"

namespace snippets {

    inline cocos2d::Vec2 calcScaleSize(const cocos2d::Vec2& bef_sz, const cocos2d::Vec2& aft_sz) {
        return {1 + ((aft_sz.x - bef_sz.x) / bef_sz.x), 1 + ((aft_sz.y - bef_sz.y) / bef_sz.y)};
    }

    inline float calcScaleSize(const float& bef_sz, const float& aft_sz) {
        return 1 + ((aft_sz - bef_sz) / bef_sz);
    }

    inline std::string getFileName(const std::string &path) {
        std::regex r(R"(((\w+)\.json)+$)");
        std::smatch m;
        std::regex_search(path, m, r);
//        if (m.s() != 3) throw std::runtime_error("snippets::getFileName: path - it's' bullshit!!\n");
        return m[2].str();
    }

    inline float calcMargin(const float& m, const float& befScreenSize, const float& aftScreenSize) {
        return (m*aftScreenSize)/befScreenSize;
    }

    template<typename T>
    inline void fixResolution(T*& img) {
        const auto fmSize = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();
        img->setScale(MIN(fmSize.width / 320, fmSize.height / 480));
    }

    inline cocos2d::Sprite* loadSpriteWithFixResolution(const std::string& path) {
        auto* r = cocos2d::Sprite::create(path);
        const auto fmSize = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();
        r->setScale(MIN(fmSize.width / 320, fmSize.height / 480));
        return r;
    }

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