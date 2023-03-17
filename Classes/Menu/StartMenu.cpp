#include "StartMenu.h"
#include "FontManager.h"

USING_NS_CC;

Scene* StartMenu::createScene()
{
    return StartMenu::create();
}

// init callback
bool StartMenu::init()
{
    if (!Scene::init()) return false;

    const auto visibleSize = Director::getInstance()->getVisibleSize();

    auto mnLevel = MenuItemLabel::create(Label::createWithTTF(FontManager::mainMenu, "Уровни"));
    auto mnExit = MenuItemLabel::create(Label::createWithTTF(FontManager::mainMenu, "Закрыть"), 
        [&](Ref* sender){
            Director::getInstance()->end();

            #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                EventCustom customEndEvent("game_scene_close_event");
                _eventDispatcher->dispatchEvent(&customEndEvent);
            #endif
        });

    auto menu = Menu::create(mnLevel, mnExit, NULL);
    menu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    menu->alignItemsVerticallyWithPadding(15);
    this->addChild(menu, 1);

    return true;
}