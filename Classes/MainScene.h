#ifndef MAIN_SCENE
#define MAIN_SCENE

#define _MAX(a,b) (((a) > (b)) ? (a) : (b))
#define _MIN(a,b) (((a) < (b)) ? (a) : (b))

#include <map>
#include "cocos2d.h"
#include "EnumIDs.h"

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // Update
    virtual void update(float dt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
    {}
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
    {}

protected:
    cocos2d::EventListenerKeyboard * mEventListener;
    States::SceneStates mState;
    cocos2d::Sprite * mBackground;

    float time = 0.f;

    std::map <cocos2d::EventKeyboard::KeyCode, bool> mapKeysPressed;

    float const animationSpeed = 1.f;
};

#endif // GAME_SCENE
