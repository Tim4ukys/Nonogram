#include "FontManager.h"

USING_NS_CC;

cocos2d::TTFConfig FontManager::mainMenu;
cocos2d::TTFConfig FontManager::logoInMainMenu;
cocos2d::TTFConfig FontManager::selectLevelTitle;
cocos2d::TTFConfig FontManager::selectLanguage;

void FontManager::init()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();

    auto calc = [&visibleSize](float fontSize) -> float { 
        return MIN(visibleSize.width * (fontSize / 320.0f), visibleSize.height * (fontSize / 480.0f)); 
    };

    mainMenu = cocos2d::TTFConfig("fonts/vga8x16.ttf", calc(21.0f));
    logoInMainMenu = cocos2d::TTFConfig("fonts/vga8x16.ttf", calc(33.0f));
    selectLevelTitle = cocos2d::TTFConfig("fonts/vga8x16.ttf", calc(18.5f));
    selectLanguage = cocos2d::TTFConfig ("fonts/vga8x16.ttf", calc(20.0f));
}
