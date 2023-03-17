#ifndef __START_MENU_H__
#define __START_MENU_H__

#include "cocos2d.h"

class StartMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(StartMenu);
};

#endif // __START_MENU_H__
