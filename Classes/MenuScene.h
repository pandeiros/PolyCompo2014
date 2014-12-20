#ifndef MENU_SCENE
#define MENU_SCENE

#include "cocos2d.h"
#include "MainScene.h"
//#include "Player.h"

class MenuScene : public MainScene {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene ();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init ();

    // Update
    virtual void update (float dt);

    // implement the "static create()" method manually
    CREATE_FUNC (MenuScene);

    virtual void onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:
    cocos2d::Menu * mMenu;
    cocos2d::MenuItemImage * mStartButton;
    cocos2d::Sprite * mWars;

    void startGame ();

};

#endif // GAME_SCENE
