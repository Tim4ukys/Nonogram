//
// Created by tim4ukys on 25.03.2023.
//

#ifndef NONOGRAM_CONFIG_HPP
#define NONOGRAM_CONFIG_HPP

#include <string_view>
#include "json.hpp"

class Config {
    nlohmann::json m_j;
    std::string_view m_fileName;

    static inline Config* s_pConfig;

public:
    explicit Config(const std::string_view &fileName);
    ~Config();

    static inline void init(const std::string_view &fileName){ s_pConfig = new Config(fileName); };
    static inline auto& getInstance() { return *s_pConfig; };

    template<typename T>
    inline auto operator[](T key) { return m_j[key]; }
};

#endif //NONOGRAM_CONFIG_HPP
