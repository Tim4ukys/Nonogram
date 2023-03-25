//
// Created by tim4ukys on 25.03.2023.
//

#ifndef NONOGRAM_LANGUAGE_HPP
#define NONOGRAM_LANGUAGE_HPP

#include <string_view>
#include "Config.hpp"

class Language {
    static inline Language* s_pLang;
    using menuItem = std::map<std::string, std::string>;
    std::map<std::string, menuItem> m_lang;

public:
    explicit Language(Config& config);

    static inline void init(Config& config){ s_pLang = new Language(config); };
    static inline auto& getInstance() { return *s_pLang; };

    inline auto& operator[](const std::string_view& key) { return m_lang[key.data()]; }
};


#endif //NONOGRAM_LANGUAGE_HPP
