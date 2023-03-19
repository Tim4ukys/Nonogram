#ifndef __FONT_MANAGER_H__
#define __FONT_MANAGER_H__

#include "cocos2d.h"

class FontManager {
public:
    static void init();

    static cocos2d::TTFConfig mainMenu;
    static cocos2d::TTFConfig logoInMainMenu;
};

#endif // __FONT_MANAGER_H__