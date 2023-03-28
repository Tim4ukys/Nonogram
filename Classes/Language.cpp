//
// Created by tim4ukys on 25.03.2023.
//

//#include <filesystem>
#include <cocos2d.h>
#include "Language.hpp"
#include "json.hpp"
#include "Snippets.hpp"

USING_NS_CC;

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

Language::Language(Config& config) {
    for (auto& file : FileUtils::getInstance()->listFiles("conf/lang/")) {
        if (!ends_with(file, ".json")) continue;

        const auto lKey = snippets::getFileName(file);
        nlohmann::json j = nlohmann::json::parse(FileUtils::getInstance()->getStringFromFile("conf/lang/" + lKey + ".json"));
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
    updateLanguage(config["language"].get<std::string>());
}