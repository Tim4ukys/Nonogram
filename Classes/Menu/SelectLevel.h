#ifndef __SELECT_LEVEL_H__
#define __SELECT_LEVEL_H__

#include "AbstractMenu.hpp"

class SelectLevel : public AbstractMenu {
public:
    static inline cocos2d::Scene* createScene() {
        return SelectLevel::create();
    }

    virtual void onAddChildToScrollView(cocos2d::Layer const* pScrollView, const float scrlWidth, float &contentSize) final;

    CREATE_FUNC(SelectLevel);
};

#endif // __SELECT_LEVEL_H__
