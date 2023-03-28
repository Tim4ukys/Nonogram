//
// Created by tim4ukys on 25.03.2023.
//

#ifndef NONOGRAM_SELECTLANGUAGE_HPP
#define NONOGRAM_SELECTLANGUAGE_HPP

#include "AbstractMenu.hpp"

class SelectLanguage : public AbstractMenu<false> {
public:
    static inline cocos2d::Scene* createScene() {
        return SelectLanguage::create();
    }

    virtual void onAddChildToLayer(cocos2d::Layer const* pMenu, const float widthLayer, float *pContentSize) final;

    CREATE_FUNC(SelectLanguage);
};


#endif //NONOGRAM_SELECTLANGUAGE_HPP
