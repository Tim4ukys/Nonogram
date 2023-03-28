//
// Created by tim4ukys on 25.03.2023.
//

#ifndef NONOGRAM_LANGUAGE_HPP
#define NONOGRAM_LANGUAGE_HPP

#include <map>
#include <utility>
#include <string_view>
#include <memory>
#include "Config.hpp"

class Language {
    friend class SelectLanguage;

    static inline std::unique_ptr<Language> s_pLang;
    using menuItem = std::map<std::string, std::string>; // переводы слов в меню по ключу
    using dataItem = std::map<std::string, menuItem>; // структура со всеми "менюшками"
    dataItem* m_curData = nullptr;
    std::map<std::string, std::pair<dataItem/* data */, std::string /* full name */>> m_lang; // все языки

public:
    explicit Language(Config& config);

    static inline void init(Config& config){ s_pLang = std::make_unique<Language>(config); };
    static inline auto& getInstance() { return *s_pLang; };

    inline void updateLanguage(const std::string& key) {
        m_curData = &m_lang[key].first;
    }

    inline auto& operator[](const std::string_view& key) { return (*m_curData)[key.data()]; }
};


#endif //NONOGRAM_LANGUAGE_HPP
