//
// Created by tim4ukys on 25.03.2023.
//

#include "Config.hpp"
#include <cocos2d.h>

USING_NS_CC;

Config::Config(const std::string_view &fileName) : m_fileName(fileName) {
    auto data = FileUtils::getInstance()->getDataFromFile(fileName.data());
    m_j = nlohmann::json::parse(std::string((char*)data.getBytes(), (size_t)data.getSize()));
}

Config::~Config() {
    FileUtils::getInstance()->writeStringToFile(m_j.dump(), m_fileName.data());
}

