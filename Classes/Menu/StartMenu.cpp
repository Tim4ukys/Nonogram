#include "StartMenu.h"
#include "FontManager.h"
#include "DefColors.hpp"

#include "SelectLevel.h"

#include "json.hpp"
#include "Snippets.hpp"

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
    {
        auto fileData = FileUtils::getInstance()->getDataFromFile("img/logo/logos.json");
        j = nlohmann::json::parse(std::string((char*)fileData.getBytes(), (size_t)fileData.getSize()));
    }

    auto logo = Sprite::create("img/logo/" + j[snippets::randomInteger(0, j.size()-1)].get<std::string>());
    logo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 158);
    const auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    logo->setScale(MIN(frameSize.width / 320, frameSize.height / 480));
    this->addChild(logo, 2);
    
    auto txtLogo = Label::createWithTTF(FontManager::logoInMainMenu, "Nonogram");
    txtLogo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + (158 - 34));
    txtLogo->setColor(DefColors::MainMenuTextLogo);
    this->addChild(txtLogo, 3);

    // ----------------
    // Menu list(1)

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