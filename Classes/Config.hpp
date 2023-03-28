//
// Created by tim4ukys on 25.03.2023.
//

#ifndef NONOGRAM_CONFIG_HPP
#define NONOGRAM_CONFIG_HPP

#include <memory>
#include <string_view>
#include "json.hpp"

class Config {
    nlohmann::json m_j;
    std::string_view m_fileName;

    static inline std::unique_ptr<Config> s_pConfig;

public:
    explicit Config(const std::string_view &fileName);
    ~Config();

    static inline void release() { s_pConfig.reset(); };
    bool save();

    static inline void init(const std::string_view &fileName){ s_pConfig = std::make_unique<Config>(fileName); };
    static inline auto& getInstance() { return *s_pConfig; };

    template<typename T>
    inline auto& operator[](T key) { return m_j[key]; }
};

#endif //NONOGRAM_CONFIG_HPP
