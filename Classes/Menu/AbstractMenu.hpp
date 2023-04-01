#ifndef __ABSTRACT_MENU_HPP__
#define __ABSTRACT_MENU_HPP__

#include <cocos2d.h>
#include <any>
#include <boost/signals2.hpp>

/**
 * Шаблон меню, которые будут вызываться из главного меню
 * @date 01.04.23
 */
class AbstractMenu : public cocos2d::Scene  {
protected:
    boost::signals2::signal<void()> m_onClickButtonBack;

    enum class WhatAdd {
        NONE,

        SCROLL_VIEW,
        MENU
    };
    WhatAdd m_nWhatAdd = WhatAdd::NONE;

public:
    bool init() override;

    /**
     * Вызывается в тот момент, когда инициализируется сцена
     * @param sucker Тот, в кого будем запихивать наш треш
     * @param widthLayer Размер доступной области
     * @param pContentSize Размер получившийся области(только при WhatAdd::SCROLL_VIEW)
     */
    virtual void onReadyAddChild(std::any sucker, float widthLayer, float *pContentSize = nullptr) = 0;
};

#endif // __ABSTRACT_MENU_HPP__