//
// Created by tim4ukys on 25.03.2023.
//

#include <filesystem>
#include <cocos2d.h>
#include "Language.hpp"
#include "json.hpp"
#include "Snippets.hpp"

USING_NS_CC;

Language::Language(Config& config) {
    for (auto& files : std::filesystem::directory_iterator(FileUtils::getInstance()->getDefaultResourceRootPath() + "conf/lang/")) {
        const auto lKey = snippets::getFileName(files.path().string());
        auto fd = FileUtils::getInstance()->getDataFromFile(files.path().string());
        nlohmann::json j = nlohmann::json::parse(std::string((char*)fd.getBytes(), (size_t)fd.getSize()));
        auto fullName = j["name"].get<std::string>();
        j.erase("name");

        dataItem dataItem1;
        for (auto& [key, data] : j.items()) {
            menuItem item;
            for (auto& [k, l] : data.items()) {
                item.insert({k, l.get<std::string>()});
            }
            dataItem1.insert({key, item});
        }
        m_lang.insert({lKey, {dataItem1, fullName}});
    }
    m_curData = &m_lang[config["language"].get<std::string>()].first;
}