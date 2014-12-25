#ifndef CREDITS_SCENE
#define CREDITS_SCENE

#include "cocos2d.h"
#include "MainScene.h"

class CreditsScene : public MainScene {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene ();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init ();

    // Update
    virtual void update (float dt);

    // implement the "static create()" method manually
    CREATE_FUNC (CreditsScene);

    virtual void onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:
    cocos2d::Menu * mMenu;
    cocos2d::MenuItemImage * mBack;
    cocos2d::Label * mText;
    cocos2d::Label * mTitles;

    std::string mTextContent = "\n\n\n\nPandeiros\nVonski\n\n\nStefan\n\n\nKNTG \"Polygon\"";
    std::string mTitlesContent = "\"IF YOU WANT PISCES, PREPARE FOR WAR!\"\n\nIT Skills Senior Supervisors:\n\n\n\nHD Graphics Tessellation Developer:\n\n\nSpecial Thanks To:\n";


    /*cocos2d::MenuItemImage * mCredits;
    cocos2d::MenuItemImage * mInsertCoin;
    cocos2d::MenuItemImage * mExit;
    cocos2d::Sprite * mWars;
    cocos2d::Sprite * mTitle;*/


    void showMenu ();

    /*float currentFrameTime = 0.f;
    Cutscenes::Menu currentSceneFrame = Cutscenes::_0_MENU_INIT;*/

    template <class Type>
    void fadeIn (Type * object, float duration) {
        object->setOpacity (_MIN (255, currentFrameTime / duration * 255));
    }

    /*template <class Type>
    void moveBy (Type * object, float duration, cocos2d::Vec2 vec, float dt) {
    if (currentFrameTime <= duration) {
    object->setPosition (object->getPosition () + vec * dt / duration);
    }
    }*/

};

#endif // MENU_SCENE
