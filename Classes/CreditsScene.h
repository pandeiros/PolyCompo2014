#ifndef CREDITS_SCENE
#define CREDITS_SCENE

#include "cocos2d.h"
#include "MainScene.h"

class CreditsScene : public MainScene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // Update
    virtual void update(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(CreditsScene);

    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:
    cocos2d::Menu * mMenu;
    cocos2d::MenuItemImage * mBack;
    cocos2d::Label * mText;
    cocos2d::Label * mTitles;

    std::string mTextContent = "\n\n\n\nPandeiros\nVonski\n\n\nStefan\n\n\nKNTG \"Polygon\"";
    std::string mTitlesContent = "\"IF YOU WANT PISCES, PREPARE FOR WAR!\"\n\nIT Skills Senior Supervisors:\n\n\n\nHD Graphics Tessellation Developer:\n\n\nSpecial Thanks To:\n";

    void showMenu();

    template <class Type>
    void fadeIn(Type * object, float duration)
    {
        object->setOpacity(_MIN(255, currentFrameTime / duration * 255));
    }
};

#endif // MENU_SCENE
