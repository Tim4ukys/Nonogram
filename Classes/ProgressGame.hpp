//
// Created by tim4ukys on 26.04.2023.
//

#ifndef NONOGRAM_PROGRESSGAME_HPP
#define NONOGRAM_PROGRESSGAME_HPP

#include <memory>
#include "json.hpp"

class ProgressGame {
    nlohmann::json m_j;

    static inline std::unique_ptr<ProgressGame> s_pProgressGame;
public:
    explicit ProgressGame();
    ~ProgressGame();

    static inline void release() { s_pProgressGame.reset(); };
    bool save();

    static inline void init(){ s_pProgressGame = std::make_unique<ProgressGame>(); };
    static inline auto& getInstance() { return *s_pProgressGame; };

    template<typename T1, typename T2>
    inline bool isExist(T1 group, T2 level) const {
        return m_j[group].size() > level;
    }

    template<typename T1, typename T2>
    inline auto& get(T1 group, T2 level, int countBoxInLine) {
        auto& arr = m_j[group];
        if (!arr.is_array()) {
            arr.clear();
            arr = nlohmann::json::array();
        }
        if (!isExist(group, level) || !arr[level].is_array()) {
            std::vector<int> tmp(countBoxInLine*countBoxInLine, 0);
            arr[level] = tmp;
        }
        return arr[level];
    }
};

#endif //NONOGRAM_PROGRESSGAME_HPP
