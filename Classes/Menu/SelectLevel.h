#ifndef __SELECT_LEVEL_H__
#define __SELECT_LEVEL_H__

#include "AbstractMenu.hpp"

class SelectLevel : public AbstractMenu {
public:
    explicit SelectLevel() {
        m_nWhatAdd = WhatAdd::SCROLL_VIEW;
    }

    void onReadyAddChild(std::any sucker, float widthLayer, float *pContentSize) override;

    static cocos2d::Scene* createScene();
    CREATE_FUNC(SelectLevel);
};

#endif // __SELECT_LEVEL_H__
