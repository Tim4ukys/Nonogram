#include "SelectLevel.h"
#include "FontManager.h"
#include "json.hpp"
#include "Snippets.hpp"
#include "DefColors.hpp"
#include "Language.hpp"

#include "ui/CocosGUI.h"

cocos2d::Scene *SelectLevel::createScene() {
    return SelectLevel::create();
}

USING_NS_CC;

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
            const float off = (widthLayer - marginSide*2)/(lCount + 1);

            *pContentSize += marginBetweenButton;
            float hBtn{};
            for (size_t i{}; i < lCount; ++i) {
                auto btn = snippets::loadSpriteWithFixResolution("img/levels/none.png");
                btn->setPosition({ marginSide + off*(i+1), *pContentSize + btn->getContentSize().height/2 });
                btn->setColor(DefColors::selectMenuRama);
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