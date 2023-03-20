#ifndef __ABSTRACT_MENU_HPP__
#define __ABSTRACT_MENU_HPP__

#include "cocos2d.h"

class AbstractMenu : public cocos2d::Scene  {
public:
    virtual bool init() final;

    virtual void onAddChildToScrollView(cocos2d::Layer const* pScrollView, const float scrlWidth, float &contentSize) = 0;
};

#endif // __ABSTRACT_MENU_HPP__