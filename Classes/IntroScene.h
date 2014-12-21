#ifndef INTRO_SCENE
#define INTRO_SCENE

#include "cocos2d.h"
#include "MainScene.h"
#include "AnimatedSprite.h"

class IntroScene : public MainScene {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene ();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init ();

    // Update
    virtual void update (float dt);

    // implement the "static create()" method manually
    CREATE_FUNC (IntroScene);

    virtual void onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:
    // Pisces
    cocos2d::Sprite * mStars;
    cocos2d::Sprite * mStarsLine;
    cocos2d::Label * mLabelPisces;

    // Bad guys
    AnimatedSprite * mDartShader;
    cocos2d::Sprite * mDeafStar;
    cocos2d::Sprite * mLaser;
    cocos2d::Sprite * mExplosion;
    cocos2d::Sprite * mFlash;
    cocos2d::Sprite * mFleet;

    // Labels
    cocos2d::Label * mLabelTop;
    cocos2d::Label * mLabelMiddle;
    cocos2d::Label * mLabelBottom;

    float currentFrameTime = 0.f;

    Cutscenes::Intro currentSceneFrame = Cutscenes::_1_SPRITE_PISCES;

    template <class Type>
    void fadeIn (Type * object, float duration) {
        object->setOpacity (_MIN (255, currentFrameTime / duration * 255));
    }

    template <class Type>
    void fadeOut (Type * object, float duration) {
        object->setOpacity (_MAX (0, 255 - currentFrameTime / duration * 255));
    }

    void zoomIn (cocos2d::Sprite * sprite, float duration) {
        sprite->setScale (_MIN (1, currentFrameTime / duration * 1.f));
    }

    template <class Type>
    void moveBy (Type * object, float duration, cocos2d::Vec2 vec, float dt) {
        if (currentFrameTime <= duration) {
            object->setPosition (object->getPosition () + vec * dt / duration);
        }
    }
};

#endif // GAME_SCENE
