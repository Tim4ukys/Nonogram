#include "StartMenu.h"
#include "FontManager.h"
#include "DefColors.hpp"

#include "SelectLevel.h"

USING_NS_CC;

Scene* StartMenu::createScene()
{
    return StartMenu::create();
}

// init callback
bool StartMenu::init()
{
    if (!Scene::init()) return false;

    // set bg color
    this->addChild(LayerColor::create(Color4B(DefColors::MenuBackground)), -1);

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto mnLevel = MenuItemLabel::create(Label::createWithTTF(FontManager::mainMenu, "Уровни"),
        [](Ref* sender) {
            Director::getInstance()->pushScene(SelectLevel::create());
        });
    auto mnExit = MenuItemLabel::create(Label::createWithTTF(FontManager::mainMenu, "Закрыть"), 
        [&](Ref* sender){
            Director::getInstance()->end();

            #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                EventCustom customEndEvent("game_scene_close_event");
                _eventDispatcher->dispatchEvent(&customEndEvent);
            #endif
        });

    auto menu = Menu::create(mnLevel, mnExit, NULL);
    menu->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    menu->alignItemsVerticallyWithPadding(15);
    this->addChild(menu, 1);

    return true;
}