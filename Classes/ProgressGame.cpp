//
// Created by tim4ukys on 26.04.2023.
//

#include "ProgressGame.hpp"
#include <cocos2d.h>

USING_NS_CC;

ProgressGame::ProgressGame() {
    try {
        auto f = FileUtils::getInstance();
        m_j = nlohmann::json::parse(f->getStringFromFile(f->getWritablePath() + "progress.json"));
    } catch (nlohmann::json::parse_error err) {
        CCLOG("fail load progress.json");
    }
}

ProgressGame::~ProgressGame() {
    save();
}

bool ProgressGame::save() {
    auto f = FileUtils::getInstance();
    return f->writeStringToFile(m_j.dump(), f->getWritablePath() + "progress.json");
}

