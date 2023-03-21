#include "AbstractMenu.hpp"
#include "DefColors.hpp"
#include "FontManager.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

bool AbstractMenu::init()
{
    if (!Scene::init()) return false;

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // set bg color
    this->addChild(LayerColor::create(DefColors::MenuBackground), -1);

    // ------------
    // Scroll view

    auto scrl = ui::ScrollView::create();
    scrl->setDirection(ui::ScrollView::Direction::VERTICAL);
    // scrl->setBackGroundColor({0xac, 0xac, 0xac});
    scrl->setBackGroundColorType(ui::Layout::BackGroundColorType::NONE);
    // scrl->setScrollBarAutoHideEnabled(true);
    scrl->setScrollBarEnabled(false);

    const float scrlWidth = visibleSize.width - 20*2;
    const float maxH = visibleSize.height - 50 /*низ*/ - 15 /*верх*/;

    // Добавляем сам контент
    float contentSize{};
    onAddChildToScrollView((Layer*)scrl, scrlWidth, contentSize);
    
    scrl->setContentSize({scrlWidth, MIN(maxH, contentSize)});
    scrl->setInnerContainerSize({scrlWidth, contentSize});
    scrl->setAnchorPoint({0.0f, 1.0f});
    scrl->setPosition({origin.x + 20, origin.y + visibleSize.height - 15});
    scrl->setBounceEnabled(contentSize > maxH);
    this->addChild(scrl);

    // ------------
    // button "go to back"

    auto back = MenuItemLabel::create(Label::createWithTTF(FontManager::mainMenu, "Назад"), [](Ref* sender){ Director::getInstance()->popScene(); });
    back->setPosition(origin.x + visibleSize.width - back->getContentSize().width/2 - 20, origin.y + back->getContentSize().height/2 + 20);
    back->setColor(DefColors::menuItemLabel);

    auto menu = Menu::create(back, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}