//
// Created by tim4ukys on 31.03.2023.
//

#ifndef NONOGRAM_GAMEMAP_HPP
#define NONOGRAM_GAMEMAP_HPP

#include <cocos2d.h>
#include <ui/CocosGUI.h>

class GameMap : public cocos2d::Scene {
    cocos2d::ui::Button* m_Buttons[4];

    float m_fPosGameRectY;

    std::vector<std::vector<bool>> m_rightDraw;
    int m_nCountBox{};
    void loadGameMapFile(const std::string& path);

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
