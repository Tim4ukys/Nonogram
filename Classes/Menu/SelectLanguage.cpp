//
// Created by tim4ukys on 25.03.2023.
//

#include "SelectLanguage.hpp"
#include <cocos2d.h>
#include "Language.hpp"
#include "Snippets.hpp"
#include "FontManager.h"
#include "Config.hpp"

USING_NS_CC;

void SelectLanguage::onAddChildToLayer(cocos2d::Layer const* pMenu, const float widthLayer, float *pContentSize) {
    m_onClickButtonBack.connect([]() {
        Config::getInstance().save();
    });

    const auto visibleSize = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    for (auto& [langKey, data] : Language::getInstance().m_lang) {
        auto label = Label::createWithTTF(FontManager::selectLanguage, data.second);
        label->setColor(DefColors::selectLanguage);
        auto flag = snippets::loadSpriteWithFixResolution("img/flag/" + langKey + ".png");

        const Size sizeLabel = { label->getContentSize() * label->getScale() };
        const Size sizeFlag = { flag->getContentSize() * label->getScale() };
        constexpr float margin = 9.f;

        const float off = (sizeFlag.width + margin + (sizeLabel.width / 2)) - ((sizeLabel.width + sizeFlag.width + margin) / 2);
//        flag->setPosition({ visibleSize.width / 2 - (sizeLabel.width + sizeFlag.width) / 2 - margin, -1*(sizeFlag.height / 2) });
        flag->setPosition({-1 * margin, 0});
        flag->setAnchorPoint({1.0f, 1 / (sizeFlag.height - sizeLabel.height)});

        label->setPosition({off, 0 });
        label->addChild(flag);

        auto ui = MenuItemLabel::create(label,
                                        [lk = langKey](Ref* sender) {
                                            Config::getInstance()["language"] = lk;
                                            Language::getInstance().updateLanguage(lk);
                                            Director::getInstance()->replaceScene(SelectLanguage::create());
                                        });
        ((cocos2d::Menu*)pMenu)->addChild(ui);
    }
    ((Menu*)pMenu)->alignItemsVerticallyWithPadding(35.f);
    ((cocos2d::Menu*)pMenu)->setPosition({origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2});
}
