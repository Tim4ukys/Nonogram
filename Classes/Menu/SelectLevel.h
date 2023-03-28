#ifndef __SELECT_LEVEL_H__
#define __SELECT_LEVEL_H__

#include "AbstractMenu.hpp"

class SelectLevel : public AbstractMenu<true> {
public:
    static inline cocos2d::Scene* createScene() {
        return SelectLevel::create();
    }

    virtual void onAddChildToLayer(cocos2d::Layer const* pScrollView, const float widthLayer, float *pContentSize) final;

    CREATE_FUNC(SelectLevel);
};

#endif // __SELECT_LEVEL_H__
