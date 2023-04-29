//
// Created by tim4ukys on 31.03.2023.
//

#include "GameMap.hpp"
#include "Snippets.hpp"
#include "DefColors.hpp"
#include "SelectLevel.h"
#include "ProgressGame.hpp"

#include "Transitions.hpp"

USING_NS_CC;

//#define DEBUG_SIDE_NUMBS

cocos2d::Scene *GameMap::createScene(const std::string& group, int levelID) {
    return GameMap::create(group, levelID);
}

bool GameMap::init() {
    if (!Scene::init()) return false;

    // set bg color(-1)
    this->addChild(LayerColor::create(Color4B(DefColors::MenuBackground)), -1);

    loadNumbs();

    addVJ();
    addButtons();
    addGameRect();

    auto& pr = ProgressGame::getInstance().get(m_levelGroup, m_nLevelID, m_nCountBox);
    for (int x{}; x < m_nCountBox*m_nCountBox; ++x) {
        m_boxMap[x]->toggle(static_cast<Box::boxState>(pr[x].get<int>()));
    }

    return true;
}

void GameMap::saveProgress() {
    auto& pr = ProgressGame::getInstance().get(m_levelGroup, m_nLevelID, m_nCountBox);
    for (int x{}; x < m_nCountBox*m_nCountBox; ++x) {
        pr[x] = m_boxMap[x]->getState();
    }
    ProgressGame::getInstance().save();
}

void GameMap::loadNumbs() {
    for (size_t i{}; i < 10; ++i)
        m_arrNumbs[i] = Sprite::create("img/game/" + std::to_string(i) + ".png");
}

void GameMap::drawNumb(const cocos2d::Rect& r, int n, drawNumbFlags flag) {
    auto getNDel = [](int n)->int {
        int r{};
        while (n != 0) {
            n /= 10;
            ++r;
        }
        return r;
    };

    bool isZero;
    const auto ndel = !(isZero = n == 0) ? getNDel(n) : 1;

    const float off{r.size.width / static_cast<float>(ndel)};

    Vec2 aftSize;
    if (flag == drawNumbFlags::numbsLeft) {
        const auto w = (9 * r.size.height) / 16;
        aftSize = { MIN(w, off), r.size.height };
    } else {
        auto h = r.size.height;
        auto w = (9 * h) / 16;
        if (w > off) {
            w = off;
            h = (16 * w) / 9;
        }
        aftSize = {w, h};
    }

    int i{};
    while (n > 0 || isZero) {
        auto sp = Sprite::createWithTexture(m_arrNumbs[n % 10]->getTexture());
        sp->setAnchorPoint({0.5f, 0.5f});
        sp->setPosition(r.origin.x + (r.size.width - aftSize.x*float(ndel)) / 2 + aftSize.x*float(ndel - ++i) + aftSize.x/2,
                        r.origin.y + r.size.height/2);
        sp->setColor(DefColors::gameMapNumbs);

        auto&& [scX, scY] = snippets::calcScaleSize(sp->getContentSize(), aftSize);
        sp->setScale(scX, scY);
        this->addChild(sp);

        isZero = false;
        n /= 10;
    }
}

void GameMap::stLoadGameMapFile(const std::string& path, std::vector<std::vector<bool>>& gmMap, int& count) {
    auto file = FileUtils::getInstance()->getStringFromFile(path);
    bool isEnded{};
    std::vector<bool> ln;
    for (char& s : file) {
        if (s == '\r') continue;

        if (s != '\n') {
            ln.push_back(s == 'X');
        } else {
            isEnded = true;
            gmMap.push_back(ln);
            ln.clear();
            continue;
        }
        if (!isEnded) ++count;
    }
    if (!ln.empty()) gmMap.push_back(ln);
}

void GameMap::getAllNumbs(GameMap::numbs_from nmb_from, int i, std::vector<int>& out) {
    if (!out.empty()) out.clear();

    int r{};
    bool old{};
    for (int x{}; x < m_nCountBox; ++x) {
        const auto t = nmb_from == numbs_from::HORIZONTAL ? m_rightDraw[i][x] : m_rightDraw[x][i];
        if (t) {
            ++r;
        } else if (old) {
            out.push_back(r);
            r = 0;
        }
        old = t;
    }
    if (old || out.empty())
        out.push_back(r);

    std::reverse(out.begin(), out.end());
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

    std::vector<int> numbs;
    for (int x{}; x < m_nCountBox; ++x) {
        getAllNumbs(numbs_from::HORIZONTAL, m_nCountBox - x - 1, numbs);

        constexpr float m_sd = 5.f;
        constexpr float m_pdwn = 2.5f;
        const auto countNumbs = numbs.size();
        const float lb = (sz_dight - static_cast<float>(countNumbs+1)*m_sd) / static_cast<float>(countNumbs);
        for (int i{}; i < countNumbs; ++i) {
#ifndef DEBUG_SIDE_NUMBS
            drawNumb({origin.x + margin_side + sz_dight - (lb + m_sd)*float(i+1),
                      origin.y + max_btn + static_cast<float>(x)*off + m_pdwn,
                      lb, off - m_pdwn*2},
                     numbs[i]);
#else
            auto t = DrawNode::create();
            const auto pos = Vec2(margin_side + sz_dight - (lb + m_sd)*float(i+1), max_btn + static_cast<float>(x)*off);
            t->drawSolidRect(pos,
                             pos + Vec2(lb, off),
                             Color4F::RED);
            this->addChild(t);
#endif
        }
    }
    for (int x{}; x < m_nCountBox; ++x) {
        getAllNumbs(numbs_from::VERTICAL, x, numbs);

        constexpr float m_sd = 2.5f;
        constexpr float m_pdwn = 5.f;
        const auto countNumbs = numbs.size();
        const float lb = (sz_dight - static_cast<float>(countNumbs+1)*m_pdwn) / static_cast<float>(countNumbs);
        for (int i{}; i < countNumbs; ++i) {
#ifndef DEBUG_SIDE_NUMBS
            drawNumb({origin.x + margin_side + sz_dight + off*static_cast<float>(x) + m_sd,
                      origin.y + m_pdwn + max_up - sz_dight + static_cast<float>(i)*(lb + m_pdwn),
                      off - m_sd*2, lb},
                     numbs[i], drawNumbFlags::numbsUp);
#else
            auto t = DrawNode::create();
            const auto pos = Vec2(margin_side + sz_dight + off*static_cast<float>(x) + m_sd, m_pdwn + max_up - sz_dight + static_cast<float>(i)*(lb + m_pdwn));
            t->drawSolidRect(pos,
                             pos + Vec2(off - m_sd*2, lb),
                             Color4F::RED);
            this->addChild(t);
#endif
        }
    }

    auto& [nvLinesW, nvLinesH] = m_arrNavLines;
    nvLinesW = DrawNode::create();
    nvLinesW->drawSolidRect(Vec2::ZERO, {sz_line_w, off}, DefColors::gameMapNVLines);
    nvLinesW->setContentSize({sz_line_w - sz_empty, off});
    nvLinesW->setPosition(origin + Vec2(margin_side + sz_dight, max_btn));
    nvLinesW->setAnchorPoint({sz_dight/(sz_line_w - sz_empty), 0.0f});
    nvLinesH = DrawNode::create();
    nvLinesH->drawSolidRect(Vec2::ZERO, {off, max_up - max_btn}, DefColors::gameMapNVLines);
    nvLinesH->setPosition(origin + Vec2(margin_side + sz_dight, max_btn));
    this->addChild(nvLinesW);
    this->addChild(nvLinesH);
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
    m_krest->setVisible(state == boxState::KREST && m_oldState != GameMap::Box::boxState::KREST);
    m_rect->setVisible(state == boxState::RECT && m_oldState != GameMap::Box::boxState::RECT);
    m_oldState = m_oldState != state ? m_oldState = state : GameMap::Box::boxState::NONE;
}

void GameMap::addButtons() {
    const auto [vs_width, vs_height] = Director::getInstance()->getOpenGLView()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    constexpr float margin_side = 25.f;
    constexpr float margin = 17.5f;
    const float btn_w = (0.5f*vs_width - 2*margin_side - margin)/2;

    m_Krest = ui::Button::create("img/game/krest.png");
    m_Krest->setScale(snippets::calcScaleSize(m_Krest->getContentSize().width, btn_w));
    m_Krest->setColor(DefColors::gameMapBTN);
    m_Krest->setAnchorPoint({1.f, 0.5f});
    m_Krest->setPosition(origin + Vec2(vs_width - margin_side, m_fPosGameRectY / 2));
    m_KrestCb = [this](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::BEGAN
            && m_arrNavLines[0]->getNumberOfRunningActions() == 0
            && m_arrNavLines[1]->getNumberOfRunningActions() == 0)
            m_boxMap[m_nPosY*m_nCountBox + m_nPosX]->toggle(Box::boxState::KREST);
    };
    m_Krest->addTouchEventListener(m_KrestCb);

    const auto sz_krest = m_Krest->getContentSize() * m_Krest->getScale();
    m_Rect = ui::Button::create("img/game/galka.png");
    m_Rect->setScale(snippets::calcScaleSize(m_Rect->getContentSize().width, btn_w));
    m_Rect->setColor(DefColors::gameMapBTN);
    m_Rect->setAnchorPoint({1.f, 0.5f});
    m_Rect->setPosition(origin + Vec2(vs_width - margin_side - btn_w - margin, m_fPosGameRectY / 2));
    m_RectCb = [this](Ref* sender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::BEGAN
            && m_arrNavLines[0]->getNumberOfRunningActions() == 0
            && m_arrNavLines[1]->getNumberOfRunningActions() == 0)
            m_boxMap[m_nPosY*m_nCountBox + m_nPosX]->toggle(Box::boxState::RECT);
    };
    m_Rect->addTouchEventListener(m_RectCb);
    this->addChild(m_Krest);
    this->addChild(m_Rect);
}

void GameMap::addVJ() {
    const auto origin = Director::getInstance()->getOpenGLView()->getVisibleOrigin();
    const auto vs_width = Director::getInstance()->getOpenGLView()->getVisibleSize().width;

    constexpr float m_sd = 25.0f;
    constexpr float m = 10.f;
    const auto btn_w = (vs_width/2 - m - m_sd)/2;

    Size sizeBtn;
    m_fPosGameRectY = 0.0f;
    for (unsigned int i{}; i < 4; ++i) {
        auto& btn = m_Buttons[i];
        btn = ui::Button::create("img/game/gm_btn.png");
        btn->addTouchEventListener(m_ButtonsCb[i] = [this, a = i](Ref* sender, ui::Widget::TouchEventType type){
            constexpr float dur_action = 0.10f;
            switch (type)
            {
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
            m_fPosGameRectY = btn_w * 2 + m_sd*2;
        }
        btn->setScale(snippets::calcScaleSize(btn->getContentSize().height, btn_w));
        btn->setColor(DefColors::gameMapBTN);
        btn->setAnchorPoint({0.5f, 0.0f});
        btn->setPosition({origin.x + (vs_width / 4), origin.y + (m_fPosGameRectY / 2)});
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
                if (tch == ui::Widget::TouchEventType::ENDED) {
                    saveProgress();
                    Transitions::getInstance().popScene();
                }
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
            case EventKeyboard::KeyCode::KEY_ENTER:
                m_KrestCb(nullptr, tch);
                m_Krest->setHighlighted(st);
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
                m_RectCb(nullptr, tch);
                m_Rect->setHighlighted(st);
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
