//
// Created by tim4ukys on 30.04.2023.
//

#ifndef NONOGRAM_TRANSITIONS_HPP
#define NONOGRAM_TRANSITIONS_HPP

#include <vector>
#include <functional>
#include <memory>

#include <cocos2d.h>
#include "Menu/StartMenu.h"

class Transitions {
public:
    using trans_t = cocos2d::Scene* ();
private:
    std::vector<std::function<trans_t>> m_scenes;

    static constexpr float duration = 0.15f;

    static inline std::unique_ptr<Transitions> s_trans;
public:
    explicit Transitions(std::function<trans_t> firstFnc) : m_scenes({firstFnc}) {}

    static inline auto& getInstance() {
        if (!s_trans) s_trans = std::make_unique<Transitions>(StartMenu::createScene);
        return *s_trans;
    }

    void pushScene(std::function<trans_t> nextFnc) {
        m_scenes.push_back(nextFnc);
        cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(duration, nextFnc(), cocos2d::Color3B(DefColors::transitionColor)));
    }
    void popScene() {
        assert(m_scenes.size() != 1 && "Scen bolshe net, dalboyob");
        m_scenes.pop_back();
        cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(duration, (*(m_scenes.end()-1))(), cocos2d::Color3B(DefColors::transitionColor)));
    }
};


#endif //NONOGRAM_TRANSITIONS_HPP
