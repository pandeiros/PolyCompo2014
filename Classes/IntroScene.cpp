#include "IntroScene.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "AnimationUtils.h"

USING_NS_CC;

Scene* IntroScene::createScene () {
    // 'scene' is an autorelease object
    auto scene = Scene::create ();

    // 'layer' is an autorelease object
    auto layer = IntroScene::create ();

    // add layer as a child to scene
    scene->addChild (layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IntroScene::init () {
    CCLOG ("INTRO SCENE START");

    if (!MainScene::init ()) {
        return false;
    }

    // HERE STARTS THE MAGIC
    scheduleUpdate ();
    mState = States::S_INTRO;

    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    Size visibleSize = Director::getInstance ()->getVisibleSize ();

    // Background
    mBackground = Sprite::create ("Background.png");
    mBackground->setPosition (Vec2 (origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild (mBackground, Layers::BACKGROUND);

    // Stars and StarLines
    mStars = Sprite::create ("StarsLight.png");
    mStarsLine = Sprite::create ("StarsLightLine.png");
    mStars->setOpacity (0);
    mStarsLine->setOpacity (0);
    mStars->setPosition (855.f + mStars->getBoundingBox ().size.width / 2, 465.f);
    mStarsLine->setPosition (855.f + mStars->getBoundingBox ().size.width / 2, 465.f);
    this->addChild (mStarsLine, Layers::SECOND_PLAN);
    this->addChild (mStars, Layers::SECOND_PLAN);

    // Bad guys
    mDartShader = AnimatedSprite::create ("vaderAnim");
    mDartShader->setOpacity (0);
    mDartShader->setPosition (500.f, 500.f);
    this->addChild (mDartShader, 3);

    // Labels
    mLabelPisces = Label::createWithSystemFont ("Pisces", "Helvetica", 15.f);
    mLabelPisces->setPosition (visibleSize.width / 2 + 300, visibleSize.height / 2 + 135);
    mLabelPisces->setOpacity (0);
    this->addChild (mLabelPisces);

    mLabelTop = Label::createWithSystemFont ("Once upon a time, in a not far away galaxy,", "Helvetica", 25.f);
    mLabelMiddle = Label::createWithSystemFont ("there were Pisces, shining peacefully among the stars.", "Helvetica", 25.f);
    mLabelBottom = Label::createWithSystemFont ("But their days were not meant to last forever...", "Helvetica", 25.f);
    mLabelTop->setPosition (150 + mLabelTop->getBoundingBox().size.width / 2, 200);
    mLabelMiddle->setPosition (160 + mLabelMiddle->getBoundingBox ().size.width / 2, 170);
    mLabelBottom->setPosition (170 + mLabelBottom->getBoundingBox ().size.width / 2, 140);
    mLabelTop->setOpacity (0);
    mLabelMiddle->setOpacity (0);
    mLabelBottom->setOpacity (0);
    this->addChild (mLabelTop);
    this->addChild (mLabelMiddle);
    this->addChild (mLabelBottom);

    return true;
}

// Update
void IntroScene::update (float dt) {
    time += dt;
    currentFrameTime += dt;

    switch (currentSceneFrame) {
        case Cutscenes::_1_SPRITE_PISCES: {
            fadeIn<Sprite> (mStars, 3.f);
            fadeIn<Sprite> (mStarsLine, 3.f);
            if ((int)time >= Cutscenes::_2_LABEL_PISCES) {
                currentSceneFrame = Cutscenes::_2_LABEL_PISCES;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_2_LABEL_PISCES: {
            fadeIn<Label> (mLabelPisces, 2.f);
            if ((int)time >= Cutscenes::_3_LABEL_TEXT_1) {
                currentSceneFrame = Cutscenes::_3_LABEL_TEXT_1;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_3_LABEL_TEXT_1: {
            fadeIn<Label> (mLabelTop, 4.f);
            if ((int)time >= Cutscenes::_4_LABEL_TEXT_2) {
                currentSceneFrame = Cutscenes::_4_LABEL_TEXT_2;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_4_LABEL_TEXT_2: {
            fadeIn<Label> (mLabelMiddle, 4.f);
            if ((int)time >= Cutscenes::_5_LABEL_TEXT_3) {
                currentSceneFrame = Cutscenes::_5_LABEL_TEXT_3;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_5_LABEL_TEXT_3: {
            fadeIn<Label> (mLabelBottom, 4.f);
            if ((int)time >= Cutscenes::_6_SHADER_INTRO) {
                currentSceneFrame = Cutscenes::_6_SHADER_INTRO;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_6_SHADER_INTRO: {
            fadeOut <Label> (mLabelBottom, 1.4f);
            fadeOut <Label> (mLabelMiddle, 1.2f);
            fadeOut <Label> (mLabelPisces, 1.f);
            fadeOut <Label> (mLabelTop, 1.f);
            fadeIn<Sprite> (mDartShader, 2.f);
            zoomIn (mDartShader, 1.f);
            if ((int)time >= Cutscenes::_7_DESTROYER_INTO) {
                currentSceneFrame = Cutscenes::_7_DESTROYER_INTO;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_7_DESTROYER_INTO: {
           
            if ((int)time >= Cutscenes::_8_DEAF_STAR) {
                currentSceneFrame = Cutscenes::_8_DEAF_STAR;
                currentFrameTime = 0.f;
            }
            break;
        }
    }
}

void IntroScene::onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ENTER: {
            Director::getInstance ()->replaceScene (TransitionFade::create (2, GameScene::createScene (), Color3B (0, 0, 0))); break;
        }
        case EventKeyboard::KeyCode::KEY_ESCAPE: {
            Director::getInstance ()->replaceScene (TransitionFade::create (1, MenuScene::createScene (), Color3B (0, 0, 0))); break;
        }
    }

    mapKeysPressed[keyCode] = true;
}

void IntroScene::onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    mapKeysPressed[keyCode] = false;
}


