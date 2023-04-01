//
// Created by tim4ukys on 25.03.2023.
//

#ifndef NONOGRAM_SELECTLANGUAGE_HPP
#define NONOGRAM_SELECTLANGUAGE_HPP

#include "AbstractMenu.hpp"

class SelectLanguage : public AbstractMenu {
public:
    explicit SelectLanguage() {
        m_nWhatAdd = WhatAdd::MENU;
    }

    void onReadyAddChild(std::any sucker, float widthLayer, float *pContentSize) override;

    static cocos2d::Scene* createScene();
    CREATE_FUNC(SelectLanguage);
};


#endif //NONOGRAM_SELECTLANGUAGE_HPP
