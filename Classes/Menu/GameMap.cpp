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

    constexpr float y = 25.0f;

    addVJ(25.0f, y);
    addButtons(y);
    m_fPosGameRectY += y*2;
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
            m_rightDraw.push_back(ln);
            ln.clear();
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
    constexpr float sz_empty = 7.5f;

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

    const auto off = (sz_line_w - sz_dight) / static_cast<float>(m_nCountBox);

    for (int i{ 1 }; i < m_nCountBox; ++i) {
        const float x = margin_side + sz_dight + off*static_cast<float>(i);
        const float y = max_up - sz_dight - off*static_cast<float>(i);
        if (i % 5 != 0) {
            line(x, max_btn, x, max_up - sz_empty, DefColors::gameMapRamka); // |
            line(margin_side + sz_empty, y, margin_side + sz_line_w, y, DefColors::gameMapRamka); // -
        } else {
            line(x, max_btn, x, max_up, DefColors::gameMapSideRamka); // |
            line(margin_side, y, margin_side + sz_line_w, y, DefColors::gameMapSideRamka); // -
        }
    }

    m_arrPositionsMap.resize(m_nCountBox*m_nCountBox);
    m_boxMap.resize(m_nCountBox*m_nCountBox);
    for (int x{}; x < m_nCountBox; ++x) {
        for (int y{}; y < m_nCountBox; ++y) {
            const auto i = y*m_nCountBox + x;
            const auto pos = origin + Vec2(sz_dight + margin_side + off*static_cast<float>(x), max_btn + off*static_cast<float>(y));
            m_arrPositionsMap[i] = pos;
            m_boxMap[i] = std::make_unique<Box>(pos, off, this);
        }
    }

    this->addChild(ln);

    constexpr float alphaNvLines = 0.25f;
    auto& [nvLinesW, nvLinesH] = m_arrNavLines;
    nvLinesW = DrawNode::create();
    nvLinesW->drawSolidRect(Vec2::ZERO, {sz_line_w - sz_empty, off}, {0.56f, 0.49f, 0.00f, alphaNvLines});
    nvLinesW->setContentSize({sz_line_w - sz_empty, off});
    nvLinesW->setPosition(origin + Vec2(margin_side + sz_dight, max_btn));
    nvLinesW->setAnchorPoint({(sz_dight - sz_empty)/(sz_line_w - sz_empty), 0.0f});
    nvLinesH = DrawNode::create();
    nvLinesH->drawSolidRect(Vec2::ZERO, {off, max_up - sz_empty - max_btn}, {0.56f, 0.49f, 0.00f, alphaNvLines});
    nvLinesH->setPosition(origin + Vec2(margin_side + sz_dight, max_btn));
    this->addChild(nvLinesW);
    this->addChild(nvLinesH);
//    nvLinesW->setPositionZ(2);
//    m_arrNavLines[0]->runAction(MoveTo::create(2, origin + Vec2(margin_side + sz_empty, max_up - sz_empty)));
//    m_arrNavLines[0]->action

//    nvLinesH = DrawNode::create();
//    nvLinesH->drawRect({0, 0}, {sz_line_w - sz_empty, off}, {1.0f, 0.87f, 0.00f, 0.50f});



//    auto bk = DrawNode::create();
//    bk->drawSolidRect({sz_dight + margin_side, max_btn}, {sz_dight + margin_side + off, max_btn + off}, DefColors::gameMapActiveBox);
//    bk->setPositionZ(-1);
//    this->addChild(bk);
}

GameMap::Box::Box(Vec2 pos, float offset, cocos2d::Scene* sc) {
    m_krest = Sprite::create("img/game/krest_2.png");
    m_krest->setAnchorPoint({0.0f, 0.0f});
    m_krest->setScale(snippets::calcScaleSize(m_krest->getContentSize().width, offset));
    m_krest->setPosition(pos);
    m_krest->setColor(Color3B(DefColors::gameMapSideRamka));
    m_krest->setVisible(false);
    sc->addChild(m_krest);
    m_rect = DrawNode::create();
    m_rect->drawSolidRect(Vec2::ZERO, {offset, offset}, DefColors::gameMapActiveBox);
    m_rect->setPosition(pos);
    m_rect->setVisible(false);
    sc->addChild(m_rect);
}

void GameMap::Box::toggle(GameMap::Box::boxState state) {
    m_krest->setVisible(state == boxState::KREST);
    m_rect->setVisible(state == boxState::RECT);
}

void GameMap::addButtons(float y) {
    const auto [vs_width, vs_height] = Director::getInstance()->getOpenGLView()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    constexpr float margin_side = 25.f;
    constexpr float margin = 17.5f;
    auto krest = ui::Button::create("img/game/krest.png"); snippets::fixResolution(krest);
    krest->setColor(DefColors::gameMapBTN);
    krest->setAnchorPoint({1.f, 0.5f});
    krest->setPosition(origin + Vec2(vs_width - margin_side, m_fPosGameRectY / 2 + y));
    krest->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                m_boxMap[m_nPosY*m_nCountBox + m_nPosX]->toggle(Box::boxState::KREST);
                break;
            default:
                break;
        }
    });

    const auto sz_krest = krest->getContentSize() * krest->getScale();
    auto galka = ui::Button::create("img/game/galka.png"); snippets::fixResolution(galka);

    galka->setColor(DefColors::gameMapBTN);
    galka->setAnchorPoint({1.f, 0.5f});
    galka->setPosition(origin + Vec2(vs_width - margin_side - sz_krest.width - margin, m_fPosGameRectY / 2 + y));
    galka->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type){
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                m_boxMap[m_nPosY*m_nCountBox + m_nPosX]->toggle(Box::boxState::RECT);
                break;
            default:
                break;
        }
    });
    this->addChild(krest);
    this->addChild(galka);
}

void GameMap::addVJ(float x, float y) {
    auto origin = Director::getInstance()->getOpenGLView()->getVisibleOrigin();
    Size sizeBtn;
    m_fPosGameRectY = 0.0f;
    for (unsigned int i{}; i < 4; ++i) {
        auto& btn = m_Buttons[i];
        btn = ui::Button::create("img/game/gm_btn.png"); snippets::fixResolution(btn);
        btn->addTouchEventListener(m_ButtonsCb[i] = [this, a = i](Ref* sender, ui::Widget::TouchEventType type){
            constexpr float dur_action = 0.10f;
            switch (type)
            {
//                case ui::Widget::TouchEventType::BEGAN:
//                    CCLOG("button[%d] began", a);
//                    break;
                case ui::Widget::TouchEventType::BEGAN:
                {
                    auto add = [this](auto& pos) {
                        if (++pos == m_nCountBox)
                            pos = 0;
                    };
                    auto sub = [this](auto& pos) {
                        if (--pos == -1)
                            pos = m_nCountBox-1;
                    };
                    if (a == 0)
                        add(m_nPosY);
                    else if (a == 2)
                        sub(m_nPosY);
                    else if (a == 1)
                        add(m_nPosX);
                    else
                        sub(m_nPosX);

                    auto nv = m_arrNavLines[a&1];
                    nv->stopAllActions();
                    nv->runAction(MoveTo::create(dur_action, m_arrPositionsMap[a&1 ? m_nPosX : m_nPosY*m_nCountBox]));
                    break;
                }
                default:
                    break;
            }

        });
        if (m_fPosGameRectY == 0.0f) {
            sizeBtn = btn->getContentSize() * btn->getScale();
            m_fPosGameRectY = sizeBtn.height * 2;
        }
        btn->setColor(DefColors::gameMapBTN);
        btn->setAnchorPoint({0.5f, 0.0f});
        btn->setPosition({origin.x + x + sizeBtn.height, origin.y + y + sizeBtn.height});
        btn->setRotation(static_cast<float>(i) * 90.0f);
        this->addChild(btn);
    }
    registrationKBJ();
}

void GameMap::registrationKBJ() {
    auto listener = EventListenerKeyboard::create();
    auto ls = [&](EventKeyboard::KeyCode keyCode, Event* event, bool st, ui::Widget::TouchEventType tch) {
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_BACK:
                Director::getInstance()->replaceScene(StartMenu::createScene());
                break;
            case EventKeyboard::KeyCode::KEY_DPAD_UP:
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                m_ButtonsCb[0](nullptr, tch);
                m_Buttons[0]->setHighlighted(st);
                break;
            case EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                m_ButtonsCb[1](nullptr, tch);
                m_Buttons[1]->setHighlighted(st);
                break;
            case EventKeyboard::KeyCode::KEY_DPAD_DOWN:
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                m_ButtonsCb[2](nullptr, tch);
                m_Buttons[2]->setHighlighted(st);
                break;
            case EventKeyboard::KeyCode::KEY_DPAD_LEFT:
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                m_ButtonsCb[3](nullptr, tch);
                m_Buttons[3]->setHighlighted(st);
                break;
            default:
                break;
        }
    };
    using namespace std::placeholders;
    listener->onKeyReleased = std::bind(ls, _1, _2, false, ui::Widget::TouchEventType::ENDED);
    listener->onKeyPressed = std::bind(ls, _1, _2, true, ui::Widget::TouchEventType::BEGAN);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
