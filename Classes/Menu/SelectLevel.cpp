#include "SelectLevel.h"
#include "FontManager.h"
#include "json.hpp"

USING_NS_CC;

cocos2d::Scene *SelectLevel::createScene()
{
    return SelectLevel::create();
}

bool SelectLevel::init()
{
    if (!Scene::init()) return false;

    /*
    auto fd = FileUtils::getInstance()->getDataFromFile("levels/levels.json");
    std::string s{(char*)fd.getBytes(), (size_t)fd.getSize()};
    
    auto pjs = nlohmann::json::parse(s);
    for (auto& levels : pjs["groups"]) {
        log("%s", levels["name"].get<std::string>().c_str());
    }
    */

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto back = MenuItemLabel::create(Label::createWithTTF(FontManager::mainMenu, "Назад"), [](Ref* sender){ Director::getInstance()->popScene(); });

    float x = origin.x + visibleSize.width - back->getContentSize().width/2 - 20;
    float y = origin.y + back->getContentSize().height/2 + 20;
    back->setPosition(Vec2(x, y));

    auto menu = Menu::create(back, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}