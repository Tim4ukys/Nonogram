//
// Created by tim4ukys on 31.03.2023.
//

#ifndef NONOGRAM_GAMEMAP_HPP
#define NONOGRAM_GAMEMAP_HPP

#include <cocos2d.h>
#include <ui/CocosGUI.h>

class GameMap : public cocos2d::Scene {
    cocos2d::ui::Button* m_Buttons[4];
    using fncTouchEventListener = void(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType);
    std::function<fncTouchEventListener> m_ButtonsCb[4];

    float m_fPosGameRectY;

    std::vector<std::vector<bool>> m_rightDraw;
    int m_nCountBox{};
    void loadGameMapFile(const std::string& path);
    enum class numbs_from { VERTICAL, HORIZONTAL };
    void getAllNumbs(numbs_from nmb_from, int i, std::vector<int>& out);

    int m_nPosX{}, m_nPosY{};
    std::vector<cocos2d::Vec2> m_arrPositionsMap;
    cocos2d::DrawNode* m_arrNavLines[2];

    class Box {
    public:
        enum class boxState {
            NONE,
            KREST,
            RECT
        };

    private:
        boxState m_oldState{boxState::NONE};

        cocos2d::Sprite* m_krest;
        cocos2d::DrawNode* m_rect;

    public:
        explicit Box(cocos2d::Vec2 pos, float offset, cocos2d::Scene* sc);
        ~Box() = default;

        void toggle(boxState state);
    };
    std::vector<std::unique_ptr<Box>> m_boxMap;

    cocos2d::ui::Button* m_Rect;
    std::function<fncTouchEventListener> m_RectCb;
    cocos2d::ui::Button* m_Krest;
    std::function<fncTouchEventListener> m_KrestCb;
    void addButtons(float y);

    void registrationKBJ();
    void addVJ(float x, float y);

    void addGameRect();

    cocos2d::Sprite* m_arrNumbs[10];
    void loadNumbs();
    enum class drawNumbFlags { numbsLeft, numbsUp };
    void drawNumb(const cocos2d::Rect& r, int n, drawNumbFlags flag = drawNumbFlags::numbsLeft);

public:
    static cocos2d::Scene* createScene(const std::string& path);

    bool init() override;

    static GameMap *create(const std::string& path) {
        GameMap *pRet = new(std::nothrow)GameMap();
        pRet->loadGameMapFile(path);

        if (pRet && pRet->init()) {
            pRet->autorelease();
            return pRet;
        }
        else {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }

};


#endif //NONOGRAM_GAMEMAP_HPP
