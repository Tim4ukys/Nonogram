//
// Created by tim4ukys on 31.03.2023.
//

#include "GameMap.hpp"
#include "Snippets.hpp"
#include "DefColors.hpp"
#include "StartMenu.h"

USING_NS_CC;

cocos2d::Scene *GameMap::createScene(const std::string& path) {
    return GameMap::create(path);
}

bool GameMap::init() {
    if (!Scene::init()) return false;

    // set bg color(-1)
    this->addChild(LayerColor::create(Color4B(DefColors::MenuBackground)), -1);

    addVJ(25.0f, 25.0f);
    addGameRect();

    return true;
}

void GameMap::loadGameMapFile(const std::string& path) {
    auto file = FileUtils::getInstance()->getStringFromFile(path);
    bool isEnded{};
    std::vector<bool> ln;
    for (char& s : file) {
        if (s != '\n') {
            ln.push_back(s == 'X');
        } else {
            isEnded = true;
            m_rightDraw.push_back(std::move(ln));
            continue;
        }
        if (!isEnded) ++m_nCountBox;
    }
}

void GameMap::addGameRect() {
    auto ln = DrawNode::create();
    const auto [vs_width, vs_height] = Director::getInstance()->getOpenGLView()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    constexpr float margin_side = 25.f;
    constexpr float margin_up = 25.f;
    constexpr float sz_dight = 50.f;

    const auto sz_line_w = vs_width - margin_side*2;
    const auto sz_line_h = vs_height - m_fPosGameRectY - margin_up;

    const auto max_up = m_fPosGameRectY + (sz_line_h/2 - sz_line_w/2) + sz_line_w;
    const auto max_btn = m_fPosGameRectY + (sz_line_h/2 - sz_line_w/2);

    auto line = [&ln, &origin](float x1, float y1, float x2, float y2, Color4F color = DefColors::gameMapSideRamka) {
        ln->drawLine(origin + Vec2(x1, y1), origin + Vec2(x2, y2), color);
    };

    line(margin_side, max_btn, margin_side + sz_line_w, max_btn);
    line(margin_side + sz_line_w, max_btn, margin_side + sz_line_w, max_up);
    line(margin_side + sz_dight, max_btn, margin_side + sz_dight, max_up);
    line(margin_side, max_up - sz_dight, margin_side + sz_line_w, max_up - sz_dight);

    const float off = (sz_line_w - sz_dight) / m_nCountBox;
    for (int i{ 1 }; i < m_nCountBox; ++i) {
        float x = margin_side + sz_dight + off*static_cast<float>(i);
        float y = max_up - sz_dight - off*static_cast<float>(i);
        line(x, max_btn, x, max_up, (i % 5 != 0) ? DefColors::gameMapRamka : DefColors::gameMapSideRamka);
        line(margin_side, y, margin_side + sz_line_w, y, (i % 5 != 0) ? DefColors::gameMapRamka : DefColors::gameMapSideRamka);
    }

    this->addChild(ln);
}

void GameMap::addVJ(float x, float y) {
    auto origin = Director::getInstance()->getOpenGLView()->getVisibleOrigin();
    Size sizeBtn;
    m_fPosGameRectY = 0.0f;
    for (unsigned int i{}; i < 4; ++i) {
        auto& btn = m_Buttons[i];
        btn = ui::Button::create("img/game/gm_btn.png"); snippets::fixResolution(btn);
        if (m_fPosGameRectY == 0.0f) {
            sizeBtn = btn->getContentSize() * btn->getScale();
            m_fPosGameRectY = (sizeBtn.height + y) * 2;
        }
        btn->setColor(DefColors::gameMapVJ);
        btn->setAnchorPoint({0.5f, 0.0f});
        btn->setPosition({origin.x + x + sizeBtn.height, origin.y + y + sizeBtn.height});
        btn->setRotation(static_cast<float>(i) * 90.0f);
        this->addChild(btn);
    }
    registrationKBJ();
}

void GameMap::registrationKBJ() {
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
//        CCLOG("keyboard: keyCode: %d", (int)keyCode);
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_DPAD_UP:
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                m_Buttons[0]->setHighlighted(true);
                break;
            case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                m_Buttons[1]->setHighlighted(true);
                break;
            case EventKeyboard::KeyCode::KEY_DPAD_DOWN:
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                m_Buttons[2]->setHighlighted(true);
                break;
            case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                m_Buttons[3]->setHighlighted(true);
                break;
            default:
                break;
        }
    };
    listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_BACK:
                Director::getInstance()->replaceScene(StartMenu::createScene());
                break;
            case EventKeyboard::KeyCode::KEY_DPAD_UP:
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                m_Buttons[0]->setHighlighted(false);
                break;
            case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                m_Buttons[1]->setHighlighted(false);
                break;
            case EventKeyboard::KeyCode::KEY_DPAD_DOWN:
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                m_Buttons[2]->setHighlighted(false);
                break;
            case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                m_Buttons[3]->setHighlighted(false);
                break;
            default:
                break;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
