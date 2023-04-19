//
// Created by tim4ukys on 31.03.2023.
//

#ifndef NONOGRAM_GAMEMAP_HPP
#define NONOGRAM_GAMEMAP_HPP

#include <cocos2d.h>
#include <ui/CocosGUI.h>
//#include <atomic>

class GameMap : public cocos2d::Scene {
    cocos2d::ui::Button* m_Buttons[4];
    std::function<void(cocos2d::Ref*, cocos2d::ui::Widget::TouchEventType)> m_ButtonsCb[4];
//    std::atomic<>;

    float m_fPosGameRectY;

    std::vector<std::vector<bool>> m_rightDraw;
    int m_nCountBox{};
    void loadGameMapFile(const std::string& path);

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
//        boxState m_oldState{boxState::NONE};

        cocos2d::Sprite* m_krest;
        cocos2d::DrawNode* m_rect;

    public:
        explicit Box(cocos2d::Vec2 pos, float offset, cocos2d::Scene* sc);
        ~Box() = default;

        void toggle(boxState state);
    };
    std::vector<std::unique_ptr<Box>> m_boxMap;

    void addButtons(float y);
    void addVJ(float x, float y);
    void addGameRect();
    void registrationKBJ();

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
