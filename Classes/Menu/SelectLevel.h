#ifndef __SELECT_LEVEL_H__
#define __SELECT_LEVEL_H__

#include "AbstractMenu.hpp"
#include "ui/UIButton.h"

class SelectLevel : public AbstractMenu {

    class GmRama : public cocos2d::ui::Button {
        bool m_bIsGood;

    public:
        void renderMap(const std::vector<int>& prMap, int countBox);

        static GmRama *create(const std::string& normalImage, bool isGood);
    };

public:
    explicit SelectLevel() {
        m_nWhatAdd = WhatAdd::SCROLL_VIEW;
    }

    void onReadyAddChild(std::any sucker, float widthLayer, float *pContentSize) override;

    static cocos2d::Scene* createScene();
    CREATE_FUNC(SelectLevel);
};

#endif // __SELECT_LEVEL_H__
