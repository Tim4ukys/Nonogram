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

//        label->setPosition(Vec2::ZERO);
        label->setAnchorPoint({0.0f, 0.5f});

        auto flag = snippets::loadSpriteWithFixResolution("img/flag/" + langKey + ".png");
        flag->setAnchorPoint({1.0f, 0.5f});
        flag->setPosition({-9.f, flag->getContentSize().height / 2});
        label->addChild(flag);
        label->setContentSize({label->getContentSize().width, flag->getContentSize().height});
        auto ui = MenuItemLabel::create(label,
                                        [lk = langKey](Ref* sender) {
                                            Config::getInstance()["language"] = lk;
                                            Language::getInstance().updateLanguage(lk);
                                            Director::getInstance()->replaceScene(SelectLanguage::create());
                                        });
        ((Menu*)pMenu)->addChild(ui);
    }
    ((Menu*)pMenu)->alignItemsVerticallyWithPadding(30.f);
    ((Menu*)pMenu)->setPosition({origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2});
}
