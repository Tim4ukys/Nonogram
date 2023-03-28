//
// Created by tim4ukys on 25.03.2023.
//

#include "Config.hpp"
#include <cocos2d.h>

USING_NS_CC;

Config::Config(const std::string_view &fileName) : m_fileName(fileName) {
    try {
        auto f = FileUtils::getInstance();
        m_j = nlohmann::json::parse(f->getStringFromFile(f->getWritablePath() + fileName.data()));
    } catch (nlohmann::json::parse_error err) {
        m_j = R"({ "language": "ru" })"_json;
    }
}

Config::~Config() {
    save();
}

bool Config::save() {
    auto f = FileUtils::getInstance();
//    std::cout << "FileUtils::getWritablePath(): " << f->getWritablePath() << std::endl;
    return f->writeStringToFile(m_j.dump(), f->getWritablePath() + m_fileName.data());
}

