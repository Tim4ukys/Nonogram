#include "StartMenu.h"
#include "FontManager.h"
#include "DefColors.hpp"
#include "Transitions.hpp"

#include "SelectLevel.h"
#include "SelectLanguage.hpp"

#include "json.hpp"
#include "Snippets.hpp"
#include "Language.hpp"

USING_NS_CC;

Scene* StartMenu::createScene()
{
    return StartMenu::create();
}

// init callback
bool StartMenu::init()
{
    if (!Scene::init()) return false;

    // set bg color(-1)
    this->addChild(LayerColor::create(Color4B(DefColors::MenuBackground)), -1);

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ---------------
    // Logo(2, 3)

    nlohmann::json j;
    snippets::loadJSON("img/logo/logos.json", j);

    auto logo = snippets::loadSpriteWithFixResolution("img/logo/" + j[snippets::randomInteger(0, j.size()-1)].get<std::string>());
    logo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 158);
    this->addChild(logo, 2);
    
    auto txtLogo = Label::createWithTTF(FontManager::logoInMainMenu, "Nonogram");
    txtLogo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + (158 - 34));
    txtLogo->setColor(DefColors::MainMenuTextLogo);
    this->addChild(txtLogo, 3);

    // ----------------
    // Menu list(1)
    auto& lang = Language::getInstance()["startMenu"];

    auto mnLevel = MenuItemLabel::create(Label::createWithTTF(FontManager::mainMenu, lang["levels"]),
        [](Ref* sender) {
            Transitions::getInstance().pushScene(SelectLevel::createScene);
        });
    auto mnSelectLang = MenuItemLabel::create(Label::createWithTTF(FontManager::mainMenu, lang["lang"]),
                                              [](Ref* sender) { Transitions::getInstance().pushScene(SelectLanguage::createScene); });
    auto mnExit = MenuItemLabel::create(Label::createWithTTF(FontManager::mainMenu, lang["exit"]),
        [](Ref* sender){
            Director::getInstance()->end();

            #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
                EventCustom customEndEvent("game_scene_close_event");
                _eventDispatcher->dispatchEvent(&customEndEvent);
            #endif
        });

    auto menu = Menu::create(mnLevel, mnSelectLang, mnExit, NULL);
    menu->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    menu->alignItemsVerticallyWithPadding(15);
    menu->setColor(DefColors::menuItemLabel);
    this->addChild(menu, 1);

    return true;
}