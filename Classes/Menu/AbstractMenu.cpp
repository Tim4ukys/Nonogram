#include "AbstractMenu.hpp"
#include "ui/CocosGUI.h"

#include "DefColors.hpp"
#include "FontManager.h"
#include "Language.hpp"
#include "StartMenu.h"

USING_NS_CC;

bool AbstractMenu::init() {
    if (!Scene::init()) return false;

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // set bg color
    this->addChild(LayerColor::create(DefColors::MenuBackground), -1);

    // ------------
    // Scroll view or empty layer

#ifdef CC_PLATFORM_PC
    constexpr float marginSide = 20.f;
#else
    constexpr float marginSide = 10.f;
#endif
    const float scrlWidth = visibleSize.width - marginSide*2;
    const float maxH = visibleSize.height - 50 /*низ*/ - 15 /*верх*/;

    switch (m_nWhatAdd) {
        case WhatAdd::SCROLL_VIEW: {
            auto scrl = ui::ScrollView::create();
            scrl->setDirection(ui::ScrollView::Direction::VERTICAL);
            // scrl->setBackGroundColor({0xac, 0xac, 0xac});
            scrl->setBackGroundColorType(ui::Layout::BackGroundColorType::NONE);
            // scrl->setScrollBarAutoHideEnabled(true);
            scrl->setScrollBarEnabled(false);

            // Добавляем сам контент
            float contentSize{};
            onReadyAddChild(scrl, scrlWidth, &contentSize);

            scrl->setContentSize({scrlWidth, MIN(maxH, contentSize)});
            scrl->setInnerContainerSize({scrlWidth, contentSize});
            scrl->setAnchorPoint({0.0f, 1.0f});
            scrl->setPosition({origin.x + marginSide, origin.y + visibleSize.height - 15});
            scrl->setBounceEnabled(contentSize > maxH);
            this->addChild(scrl);
            break;
        }
        case WhatAdd::MENU: {
            auto menu = Menu::create();
            onReadyAddChild(menu, scrlWidth, (float *) &maxH);
            this->addChild(menu);
            break;
        }
        default:
            onReadyAddChild((Scene*)this, scrlWidth, nullptr);
            break;
    }

    // ------------
    // button "go to back"

    auto back = MenuItemLabel::create(
            Label::createWithTTF(FontManager::mainMenu, Language::getInstance()["absMenu"]["back"]),
            [&](Ref* sender){
                m_onClickButtonBack();
                Director::getInstance()->replaceScene(StartMenu::create());
            }
    );
    back->setPosition(origin.x + visibleSize.width - back->getContentSize().width/2 - 20, origin.y + back->getContentSize().height/2 + 20);
    back->setColor(DefColors::menuItemLabel);

    auto menu = Menu::create(back, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
            Director::getInstance()->replaceScene(StartMenu::createScene());
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
