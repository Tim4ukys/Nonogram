#ifndef __DEF_COLORS_HPP__
#define __DEF_COLORS_HPP__

#include "cocos2d.h"

#include <type_traits>

class DefColors {
public:
    static inline const cocos2d::Color4B MenuBackground{20, 17, 26, 0xff};
    static inline const cocos2d::Color3B MainMenuTextLogo{158, 149, 171};
    static inline const cocos2d::Color3B menuItemLabel{160, 151, 189};

    static inline const cocos2d::Color3B selectMenuTitle{menuItemLabel};
    static inline const cocos2d::Color3B selectMenuRama{74, 74, 74};
    static inline const cocos2d::Color3B selectMenuGood{49, 84, 55};

    static inline const cocos2d::Color3B selectLanguage{menuItemLabel};

    static inline const cocos2d::Color3B gameMapBTN{menuItemLabel};
    static inline const cocos2d::Color4F gameMapSideRamka{ 0.55f, 0.55f, 0.65f, 1.f };
    static inline const cocos2d::Color4F gameMapRamka{ 0.35f, 0.35f, 0.45f, 1.f };
    static inline const cocos2d::Color4F gameMapActiveBox{0.65f, 0.70f, 0.79f, 1.f};
    static inline const cocos2d::Color4F gameMapDisableBox{0.25f, 0.25f, 0.45f, 1.f};
    static inline const cocos2d::Color4F gameMapNVLines{0.56f, 0.49f, 0.00f, 0.25f};
    static inline const cocos2d::Color3B gameMapNumbs{menuItemLabel};
};

#endif // __DEF_COLORS_HPP__
