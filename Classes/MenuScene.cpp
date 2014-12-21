#include "MenuScene.h"
#include "IntroScene.h"

USING_NS_CC;

Scene* MenuScene::createScene () {
    // 'scene' is an autorelease object
    auto scene = Scene::create ();

    // 'layer' is an autorelease object
    auto layer = MenuScene::create ();

    // add layer as a child to scene
    scene->addChild (layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init () {
    CCLOG ("MENU SCENE START");

    if (!MainScene::init ()) {
        return false;
    }

    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    Size visibleSize = Director::getInstance ()->getVisibleSize ();

    // Config
    scheduleUpdate ();
    mState = States::S_MENU;

    // Bakcround
    mBackground = Sprite::create ("Background.png");
    mBackground->setPosition (Vec2 (origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild (mBackground, Layers::BACKGROUND);

    // Buttons
    mStart = MenuItemImage::create ("ButtonEmpty.png", "ButtonFull.png", CC_CALLBACK_0 (MenuScene::startGame, this));
    mStart->setPosition (visibleSize.width / 2.f, visibleSize.height / 2.f + mStart->getBoundingBox ().size.height / 2 - 140);
    mStart->setScale (0.5f);
    mStart->setOpacity (0);

    mCredits = MenuItemImage::create ("placeholder.png", "placeholder.png", CC_CALLBACK_0 (MenuScene::showCredits, this));
    mCredits->setPosition (150.f,150.f);
    mCredits->setOpacity (0);

    mExit = MenuItemImage::create ("placeholder.png", "placeholder.png", CC_CALLBACK_0 (MenuScene::exitGame, this));
    mExit->setPosition (visibleSize.width - 150.f, 150.f);
    mExit->setOpacity (0);

    // "Wars" sprite
    mWars = Sprite::create ("Wars.png");
    mWars->setScale (0.5f);
    mWars->setPosition (visibleSize.width / 2.f, visibleSize.height / 2.f - mWars->getBoundingBox ().size.height / 2 - 115);
    mWars->setOpacity (0);
    this->addChild (mWars, Layers::GUI);

    mMenu = Menu::create (mStart, mCredits, mExit, NULL);
    mMenu->setPosition (Vec2::ZERO);
    this->addChild (mMenu, Layers::GUI);

    // Title
    mTitle = Sprite::create ("Title.png");
    mTitle->setPosition (visibleSize.width / 2.f, visibleSize.height - 370.f);
    this->addChild (mTitle, Layers::GUI);

    // Actions
    moveTitle = MoveBy::create (2, Vec2 (0.f, 200.f));
    showGUI = FadeIn::create (0.5);

    return true;
}

// Update
void MenuScene::update (float dt) {
    time += dt;
    currentFrameTime += dt;

    switch (currentSceneFrame) {
        case Cutscenes::_0_MENU_INIT: {
            if ((int)time >= Cutscenes::_1_MOVE_TITLE) {
                currentSceneFrame = Cutscenes::_1_MOVE_TITLE;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_1_MOVE_TITLE: {
            moveBy<Sprite> (mTitle, 2.f, Vec2 (0.f, 150.f), dt);
            if ((int)time >= Cutscenes::_2_SHOW_GUI) {
                currentSceneFrame = Cutscenes::_2_SHOW_GUI;
                currentFrameTime = 0.f;
            }
            break;
        }
        case Cutscenes::_2_SHOW_GUI: {
            fadeIn<MenuItem> (mStart, 0.5f);
            fadeIn<MenuItem> (mCredits, 0.5f);
            fadeIn<MenuItem> (mExit, 0.5f);
            fadeIn<Sprite> (mWars, 0.5f);
            if ((int)time >= Cutscenes::_3_BLINK_START_BUTTON) {
                currentSceneFrame = Cutscenes::_3_BLINK_START_BUTTON;
                currentFrameTime = 0.f;
            }
            break;
        }

        case Cutscenes::_3_BLINK_START_BUTTON: {
            // Flashing start button
            if (currentFrameTime > 0.6f) {
                currentFrameTime = 0.f;
                if (isStartActive) {
                    mStart->setNormalImage (Sprite::create ("ButtonEmpty.png"));
                }
                else {
                    mStart->setNormalImage (Sprite::create ("ButtonFull.png"));
                }
                isStartActive = !isStartActive;
            }
            break;
        }
    }
}

void MenuScene::onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_ESCAPE: {
            Director::getInstance ()->end (); break;
        }
    }
}

void MenuScene::onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

}

void MenuScene::startGame () {
    Director::getInstance ()->replaceScene (TransitionFade::create (1, IntroScene::createScene (), Color3B (0, 0, 0)));
}

void MenuScene::showCredits () {
    //Director::getInstance ()->replaceScene (TransitionFade::create (1, CreditsScene::createScene (), Color3B (0, 0, 0)));
}

void MenuScene::exitGame () {
    Director::getInstance ()->end ();
}