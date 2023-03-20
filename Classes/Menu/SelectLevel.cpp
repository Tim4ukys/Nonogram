#include "SelectLevel.h"
#include "FontManager.h"
#include "DefColors.hpp"
#include "json.hpp"

#include "ui/CocosGUI.h"

USING_NS_CC;

void SelectLevel::onAddChildToScrollView(Layer const *pScrollView, const float scrlWidth, float &contentSize)
{
    for (int i{}; i < 50; ++i) {
        auto btn = Label::createWithTTF("ZZZZZZ VVVVVV", "fonts/vga8x16.ttf", 16.f);
        const float h = 15 + btn->getContentSize().height;
        contentSize += h;
        btn->setPosition({scrlWidth/2.f, i*h + 15});
        ((ui::ScrollView*)pScrollView)->addChild(btn);
    }
}