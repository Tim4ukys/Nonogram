#ifndef __SELECT_LEVEL_H__
#define __SELECT_LEVEL_H__

#include "cocos2d.h"

class SelectLevel : public cocos2d::Scene {

    class SelectLayer : public cocos2d::Layer {
    public:
        static inline cocos2d::Layer* createLayer() { return SelectLayer::create(); }

        CREATE_FUNC(SelectLayer);
    };

public:
    static inline cocos2d::Scene* createScene() { return SelectLevel::create(); }

    virtual bool init() final;
    
    CREATE_FUNC(SelectLevel);
};

#endif // __SELECT_LEVEL_H__
