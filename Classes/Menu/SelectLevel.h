#ifndef __SELECT_LEVEL_H__
#define __SELECT_LEVEL_H__

#include "cocos2d.h"

class SelectLevel : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() final;
    
    CREATE_FUNC(SelectLevel);
};

#endif // __SELECT_LEVEL_H__
