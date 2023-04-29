#include "SelectLevel.h"
#include "FontManager.h"
#include "json.hpp"
#include "Snippets.hpp"
#include "DefColors.hpp"
#include "Language.hpp"
#include "GameMap.hpp"
#include "ProgressGame.hpp"
#include "Transitions.hpp"

#include "ui/CocosGUI.h"

cocos2d::Scene *SelectLevel::createScene() {
    return SelectLevel::create();
}

USING_NS_CC;

SelectLevel::GmRama* SelectLevel::GmRama::create(const std::string &normalImage, bool isGood) {
    GmRama *pRet = new(std::nothrow)GmRama();

    if (pRet && pRet->init(normalImage,"","",TextureResType::LOCAL)) {
        pRet->m_bIsGood = isGood;
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

void SelectLevel::GmRama::renderMap(const std::vector<int>& prMap, int countBox) {
    constexpr int rama_sz = 6;
    constexpr int rama = 60;

    auto sc = Scene::create();
    auto sp = Sprite::create(_normalFileName);
    sp->setAnchorPoint({0.0f, 0.0f});
    sp->setColor(!m_bIsGood ? DefColors::selectMenuRama : DefColors::selectMenuGood);
    sc->addChild(sp);

    auto [width, height] = sp->getContentSize();

    const auto rm_sz = (width * float(rama_sz)) / float(rama);
    auto off = (width - rm_sz*2) / float(countBox);
    auto nd = DrawNode::create();
    for (int kx{}; kx < countBox; ++kx) {
        for (int ky{}; ky < countBox; ++ky) {
            if (prMap[(countBox - ky - 1)*countBox + kx] != 2) continue;
            nd->drawSolidRect({rm_sz + static_cast<float>(kx)*off, rm_sz + static_cast<float>(ky)*off},
                              {rm_sz + static_cast<float>(kx+1)*off, rm_sz + static_cast<float>(ky+1)*off},
                              DefColors::gameMapActiveBox);
        }
    }
    sc->addChild(nd);

    auto t = RenderTexture::create(static_cast<int>(std::ceil(width)), static_cast<int>(height));
    t->retain();
    t->begin();
    sc->visit();
    t->end();
//    Sprite::createWithTexture(t->getSprite()->getTexture());
    _buttonNormalRenderer->initWithTexture(t->getSprite()->getTexture());
//    _contentSize = Vec2(rama, rama);
}

void SelectLevel::onReadyAddChild(std::any sucker, float widthLayer, float *pContentSize)
{
    auto pScrollView = std::any_cast<ui::ScrollView*>(sucker);
    nlohmann::json j;
    snippets::loadJSON("levels/levels.json", j);
    auto& lang = Language::getInstance()["selectLevel"];

#ifdef CC_PLATFORM_PC
    constexpr float marginSide = 1.5f;
#else
    constexpr float marginSide = 0.0f;
#endif
    constexpr float marginBetweenButton = 7.5f;
    constexpr float marginBetweenGR = 13.5f;
    constexpr float glMagrin = 15.f;
    constexpr int maxCount = 5;

    constexpr float sf_margin = 17.5f;
    const auto w_btn = (widthLayer - 2*marginSide - 4*sf_margin)/5;

    *pContentSize += glMagrin;

    for (auto& level : j) {
        int countLevel{level["count"].get<int>()};
        int lCount;
        for (int x{}; x < countLevel; x += lCount) {
            if (countLevel % maxCount != 0) {
                lCount = countLevel - int(countLevel / maxCount)*maxCount;
                countLevel -= lCount;
            } else {
                lCount = maxCount;
            }
            const float off = (widthLayer - marginSide*2)/static_cast<float>(lCount + 1);

            *pContentSize += marginBetweenButton;
            float hBtn{};
            for (size_t i{}; i < lCount; ++i) {
                int countBox = 0;
                std::vector<std::vector<bool>> rightMap;
                const auto levelGroup = level["codename"].get<std::string>();
                const auto levelID = level["count"].get<int>() - (x + lCount) + i;
                GameMap::stLoadGameMapFile("levels/" + levelGroup + "/" + std::to_string(levelID),
                                           rightMap, countBox);
                auto& progr = ProgressGame::getInstance().get(level["codename"].get<std::string>(), levelID, countBox);
                bool goodMap{true};
                bool isEmptyMap{true};
                for (int kx{}; kx < countBox; ++kx) {
                    for (int ky{}; ky < countBox; ++ky) {
                        const auto r = rightMap[ky][kx];
                        const auto pr = progr[(countBox - ky - 1)*countBox + kx].get<int>();
                        if (r != (pr == 2))
                            goodMap = false;
                        if (pr != 0)
                            isEmptyMap = false;
                    }
                }

                auto btn = GmRama::create(isEmptyMap ? "img/levels/none.png" : "img/levels/rama.png", goodMap);
                if (!isEmptyMap) {
                    btn->renderMap(progr.get<std::vector<int>>(), countBox);
                } else {
                    btn->setColor(DefColors::selectMenuRama);
                }

                btn->setScale(snippets::calcScaleSize(btn->getContentSize().width, w_btn));
                btn->setPosition({ marginSide + off*(i+1), *pContentSize + btn->getContentSize().height/2 });
                btn->addClickEventListener(
                        [n = levelID, lv = level["codename"].get<std::string>()](Ref* sender){
                            CCLOG("Level number %zu in %s", n, lv.c_str());
                            Transitions::getInstance().pushScene(std::bind(GameMap::createScene, lv, static_cast<int>(n)));
                        });
                if (hBtn == 0.0f) hBtn = btn->getContentSize().height * btn->getScaleY();
                pScrollView->addChild(btn);
            }
            *pContentSize += hBtn;
        }

        *pContentSize += 3.5f;
        auto titleLG = Label::createWithTTF(FontManager::selectLevelTitle, lang[level["codename"].get<std::string>()]);
        titleLG->setPosition({widthLayer/2, *pContentSize + titleLG->getContentSize().height/2});
        titleLG->setColor(DefColors::selectMenuTitle);
        *pContentSize += marginBetweenGR + titleLG->getContentSize().height;
        pScrollView->addChild(titleLG);
    }
}