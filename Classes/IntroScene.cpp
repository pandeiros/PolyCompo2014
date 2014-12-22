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
    //time = Cutscenes::_8_DEAF_STAR;

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
    this->addChild (mStarsLine, Layers::FRONT);
    this->addChild (mStars, Layers::SECOND_PLAN);

    // Bad guys
    mDartShader = AnimatedSprite::create ("vaderAnim");
    mDartShader->setOpacity (0);
    mDartShader->setPosition (300.f, 500.f);
    this->addChild (mDartShader, Layers::ENTITIES);

    mDeafStar = Sprite::create ("DeafStar.png");
    mDeafStar->setPosition (-150.f, 319.f);
    this->addChild (mDeafStar, Layers::ENTITIES);

    // Laser
    mLaser = Sprite::create ("DeafStarLasers.png");
    mLaser->setOpacity (0);
    mLaser->setAnchorPoint (Vec2 (0.f, 0.f));
    mLaser->setPosition (155.f, 225.f);
    mDeafStar->addChild (mLaser, Layers::FRONT);

    // Explosion
    mExplosion = Sprite::create ("Explosion.png");
    mExplosion->setOpacity (0);
    mExplosion->setPosition (265.f, 225.f);
    mStarsLine->addChild (mExplosion, Layers::FRONT);

    mFlash = Sprite::create ("flash.png");
    mFlash->setOpacity (0);
    mFlash->setAnchorPoint (Vec2 (0.f, 0.f));
    mFlash->setPosition (0.f, 0.f);
    this->addChild (mFlash, Layers::FRONT);

    // Fleet
    mFleet = Sprite::create ("desTroyArrsFleet.png");
    mFleet->setOpacity (0);
    mFleet->setPosition (400.f, 400.f);
    this->addChild (mFleet, Layers::SECOND_PLAN);


    // Labels
    mLabelPisces = Label::createWithTTF ("Pisces", "fonts/DKCoolCrayon.ttf", 20.f);
    mLabelPisces->setPosition (visibleSize.width / 2 + 300, visibleSize.height / 2 + 125);
    mLabelPisces->setOpacity (0);
    this->addChild (mLabelPisces, Layers::GUI);

    mLabelTop = Label::createWithTTF (Cutscenes::intro1, "fonts/TaraType.ttf", 25.f);
    mLabelMiddle = Label::createWithTTF (Cutscenes::intro2, "fonts/TaraType.ttf", 25.f);
    mLabelBottom = Label::createWithTTF (Cutscenes::intro3, "fonts/TaraType.ttf", 25.f);
    mLabelTop->setPosition (150 + mLabelTop->getBoundingBox ().size.width / 2, 150);
    mLabelMiddle->setPosition (160 + mLabelMiddle->getBoundingBox ().size.width / 2, 120);
    mLabelBottom->setPosition (170 + mLabelBottom->getBoundingBox ().size.width / 2, 90);
    mLabelTop->setOpacity (0);
    mLabelMiddle->setOpacity (0);
    mLabelBottom->setOpacity (0);
    this->addChild (mLabelTop, Layers::GUI);
    this->addChild (mLabelMiddle, Layers::GUI);
    this->addChild (mLabelBottom, Layers::GUI);

    return true;
}

// Update
void IntroScene::update (float dt) {
    time += animationSpeed * dt;
    currentFrameTime += animationSpeed *  dt;

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
            fadeOut <Label> (mLabelTop, 1.f);
            fadeIn<Sprite> (mDartShader, 2.f);
            zoomIn (mDartShader, 2.f);
            if ((int)time >= Cutscenes::_6a_SHADER_TEXT) {
                mLabelTop->setString (Cutscenes::intro4);
                mLabelMiddle->setString (Cutscenes::intro5);
                mLabelTop->setPosition (150 + mLabelTop->getBoundingBox ().size.width / 2, 150);
                mLabelMiddle->setPosition (160 + mLabelMiddle->getBoundingBox ().size.width / 2, 120);

                currentSceneFrame = Cutscenes::_6a_SHADER_TEXT;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_6a_SHADER_TEXT: {
            fadeIn <Label> (mLabelMiddle, 4.f);
            fadeIn <Label> (mLabelTop, 4.f);
            if ((int)time >= Cutscenes::_7_DESTROYER_INTRO) {
                currentSceneFrame = Cutscenes::_7_DESTROYER_INTRO;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_7_DESTROYER_INTRO: {
            fadeIn <Sprite> (mFleet, 2.f);
            moveBy <Sprite> (mFleet, 2.f, Vec2 (20.f, 0.f), animationSpeed * dt);
            fadeOut <Label> (mLabelMiddle, 1.f);
            fadeOut <Label> (mLabelTop, 1.f);
            if ((int)time >= Cutscenes::_7a_DESTROYER_TEXT) {
                mLabelTop->setString (Cutscenes::intro6);
                mLabelMiddle->setString (Cutscenes::intro7);
                mLabelBottom->setString (Cutscenes::intro8);
                mLabelTop->setPosition (150 + mLabelTop->getBoundingBox ().size.width / 2, 150);
                mLabelMiddle->setPosition (160 + mLabelMiddle->getBoundingBox ().size.width / 2, 120);
                mLabelBottom->setPosition (170 + mLabelBottom->getBoundingBox ().size.width / 2, 90);

                currentSceneFrame = Cutscenes::_7a_DESTROYER_TEXT;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_7a_DESTROYER_TEXT: {
            moveBy <Sprite> (mFleet, 6.f, Vec2 (60.f, 0.f), animationSpeed * dt);
            fadeIn <Label> (mLabelMiddle, 3.f);
            fadeIn <Label> (mLabelTop, 3.f);
            if ((int)time >= Cutscenes::_8_DEAF_STAR) {
                currentSceneFrame = Cutscenes::_8_DEAF_STAR;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_8_DEAF_STAR: {
            fadeOut <Label> (mLabelMiddle, 1.f);
            fadeOut <Label> (mLabelTop, 1.f);
            fadeOut<Sprite> (mDartShader, 1.f);
            fadeIn <Label> (mLabelBottom, 3.f);
            moveBy <Sprite> (mDeafStar, 8.f, Vec2 (395.f, 0.f), animationSpeed * dt);
            moveBy <Sprite> (mFleet, 8.f, Vec2 (80.f, 0.f), animationSpeed * dt);
            if ((int)time >= Cutscenes::_9_LASER) {
                mDeafStar->setTexture ("DeafStarRage.png");
                currentSceneFrame = Cutscenes::_9_LASER;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_9_LASER: {
            fadeIn<Sprite> (mLaser, 2.f);
            moveBy <Sprite> (mFleet, 2.f, Vec2 (20.f, 0.f), animationSpeed * dt);
            fadeOut <Label> (mLabelBottom, 1.f);
            if ((int)time >= Cutscenes::_9a_LASER_TEXT) {
                mLabelTop->setString (Cutscenes::intro10);
                mLabelMiddle->setString (Cutscenes::intro11);
                mLabelBottom->setString (Cutscenes::intro9);
                mLabelTop->setPosition (150 + mLabelTop->getBoundingBox ().size.width / 2, 150);
                mLabelMiddle->setPosition (160 + mLabelMiddle->getBoundingBox ().size.width / 2, 120);
                mLabelBottom->setPosition (170 + mLabelBottom->getBoundingBox ().size.width / 2, 90);

                currentSceneFrame = Cutscenes::_9a_LASER_TEXT;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_9a_LASER_TEXT: {
            moveBy <Sprite> (mFleet, 5.f, Vec2 (50.f, 0.f), animationSpeed * dt);
            fadeIn <Label> (mLabelBottom, 2.f);
            fadeIn<Sprite> (mExplosion, 3.f);
            zoomIn (mExplosion, 3.f);
            if ((int)time >= Cutscenes::_10_FLASH) {
                currentSceneFrame = Cutscenes::_10_FLASH;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_10_FLASH: {
            moveBy <Sprite> (mFleet, 2.f, Vec2 (20.f, 0.f), animationSpeed * dt);
            fadeIn<Sprite> (mFlash, 2.f);
            if ((int)time >= Cutscenes::_11_AQUARIUS) {
                mLabelBottom->setString (Cutscenes::intro12);
                mLabelBottom->setPosition (170 + mLabelBottom->getBoundingBox ().size.width / 2, 90);
                mBackground->setTexture ("gameBackground.png");

                currentSceneFrame = Cutscenes::_11_AQUARIUS;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_11_AQUARIUS: {
            fadeOut<Sprite> (mFlash, 1.f);
            mStars->setOpacity (0); 
            mStarsLine->setOpacity (0);
            mLabelPisces->setOpacity (0);
            mDartShader->setOpacity (0);
            mDeafStar->setOpacity (0);
            mLaser->setOpacity (0);
            mExplosion->setOpacity (0);
            mFleet->setOpacity (0);
            fadeIn <Label> (mLabelMiddle, 4.f);
            fadeIn <Label> (mLabelTop, 4.f);
            fadeIn <Label> (mLabelBottom, 4.f);
            if ((int)time >= Cutscenes::_12_CONTINUE) {
                mLabelBottom->setString (Cutscenes::intro13);
                mLabelBottom->setPosition (170 + mLabelBottom->getBoundingBox ().size.width / 2, 90);
                mLabelBottom->setOpacity (0);

                currentSceneFrame = Cutscenes::_12_CONTINUE;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_12_CONTINUE: {
            fadeOut <Label> (mLabelMiddle, 0.5f);
            fadeOut <Label> (mLabelTop, 0.5f);
            fadeIn <Label> (mLabelBottom, 2.f);
            break;
        }
    }
}

void IntroScene::onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ENTER: case EventKeyboard::KeyCode::KEY_KP_ENTER: {
            Director::getInstance ()->replaceScene (TransitionFade::create (2, GameScene::createScene (), Color3B (0, 0, 0))); break;
        }
        case EventKeyboard::KeyCode::KEY_ESCAPE: {
            Director::getInstance ()->replaceScene (TransitionFade::create (2, MenuScene::createScene (), Color3B (0, 0, 0))); break;
        }
    }

    mapKeysPressed[keyCode] = true;
}

void IntroScene::onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    mapKeysPressed[keyCode] = false;
}


