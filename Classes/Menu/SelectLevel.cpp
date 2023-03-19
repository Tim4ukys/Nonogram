#include "SelectLevel.h"
#include "FontManager.h"
#include "DefColors.hpp"
#include "json.hpp"

#include "ui/CocosGUI.h"

USING_NS_CC;

bool SelectLevel::init()
{
    if (!Scene::init()) return false;

    // set bg color
    this->addChild(LayerColor::create(DefColors::MenuBackground), -1);

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

    auto scrl = ui::ScrollView::create();
    scrl->setDirection(ui::ScrollView::Direction::VERTICAL);
    // scrl->setBackGroundColor({0xac, 0xac, 0xac});
    scrl->setBackGroundColorType(ui::Layout::BackGroundColorType::NONE);
    // scrl->setScrollBarAutoHideEnabled(true);
    scrl->setScrollBarEnabled(false);

    const float srclWidth = visibleSize.width - 20*2;
    const float maxH = visibleSize.height - 50 /*низ*/ - 15 /*верх*/;
    
    float contentSize{};
    for (int i{}; i < 50; ++i) {
        auto btn = Label::createWithTTF("ZZZZZZ VVVVVV", "fonts/vga8x16.ttf", 16.f);
        const float h = 15 + btn->getContentSize().height;
        contentSize += h;
        btn->setPosition({srclWidth/2.f, i*h + 15});
        scrl->addChild(btn);
    }
    
    scrl->setContentSize({srclWidth, MIN(maxH, contentSize)});
    scrl->setInnerContainerSize({srclWidth, contentSize});
    scrl->setAnchorPoint({0.0f, 1.0f});
    scrl->setPosition({origin.x + 20, origin.y + visibleSize.height - 15});
    scrl->setBounceEnabled(contentSize > maxH);
    this->addChild(scrl);

    auto back = MenuItemLabel::create(Label::createWithTTF(FontManager::mainMenu, "Назад"), [](Ref* sender){ Director::getInstance()->popScene(); });

    const float x = origin.x + visibleSize.width - back->getContentSize().width/2 - 20;
    const float y = origin.y + back->getContentSize().height/2 + 20;
    back->setPosition(Vec2(x, y));

    auto menu = Menu::create(back, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}
