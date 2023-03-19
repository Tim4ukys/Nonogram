#include "FontManager.h"

USING_NS_CC;

cocos2d::TTFConfig FontManager::mainMenu;
cocos2d::TTFConfig FontManager::logoInMainMenu;

void FontManager::init()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();

    auto calcW = [](float fontSize) -> float { return fontSize / 320.f; };
    auto calcH = [](float fontSize) -> float { return fontSize / 480.f; };

    mainMenu = cocos2d::TTFConfig("fonts/vga8x16.ttf", MIN(visibleSize.width * calcW(21.f), visibleSize.height * calcH(21.f)));
    logoInMainMenu = cocos2d::TTFConfig("fonts/vga8x16.ttf", MIN(visibleSize.width * calcW(33.f), visibleSize.height * calcH(33.f)));
}
