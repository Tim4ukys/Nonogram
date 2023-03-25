//
// Created by tim4ukys on 25.03.2023.
//

#include "Language.hpp"
#include "json.hpp"
#include "Snippets.hpp"

Language::Language(Config& config) {
    nlohmann::json j;
    snippets::loadJSON("conf/lang/" + config["language"].get<std::string>() + ".json", j);

    for (auto& [key, data] : j.items()) {
        menuItem item;
        for (auto& [k, l] : data.items()) {
            item.insert({k, l.get<std::string>()});
        }
        m_lang.insert({key, item});
    }
}