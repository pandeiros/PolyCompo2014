#include "CreditsScene.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* CreditsScene::createScene () {
    // 'scene' is an autorelease object
    auto scene = Scene::create ();

    // 'layer' is an autorelease object
    auto layer = CreditsScene::create ();

    // add layer as a child to scene
    scene->addChild (layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CreditsScene::init () {
    CCLOG ("CREDITS SCENE START");

    if (!MainScene::init ()) {
        return false;
    }

    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();
    Size visibleSize = Director::getInstance ()->getVisibleSize ();

    // Config
    scheduleUpdate ();
    mState = States::S_MENU;

    // Bakcround
    mBackground = Sprite::create ("backgrounds/Background.png");
    mBackground->setPosition (Vec2 (origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild (mBackground, Layers::BACKGROUND);

    // Buttons
    mBack = MenuItemImage::create ("gui/backButton.png", "gui/backButton.png", CC_CALLBACK_0 (CreditsScene::showMenu, this));
    mBack->setPosition (100.f, 50.f);
    mBack->setScale (0.5f);

    mMenu = Menu::create (mBack, NULL);
    mMenu->setPosition (Vec2::ZERO);
    this->addChild (mMenu, Layers::GUI);

    // Text
    mText = Label::createWithTTF (mTextContent, "fonts/DKCoolCrayon.ttf", 35.f);
    mText->setPosition (visibleSize.width / 2, visibleSize.height / 2 + 50.f);
    mText->setAlignment (cocos2d::TextHAlignment::LEFT);
    this->addChild (mText, Layers::GUI);

    // Content
    mTitles = Label::createWithTTF (mTitlesContent, "fonts/DKCoolCrayon.ttf", 35.f);
    mTitles->setColor (cocos2d::Color3B::YELLOW);
    mTitles->setPosition (visibleSize.width / 2, visibleSize.height / 2 + 50.f);
    this->addChild (mTitles, Layers::GUI);

    return true;
}

// Update
void CreditsScene::update (float dt) {
    time += dt;
    //currentFrameTime += dt;
}

void CreditsScene::onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
  
}

void CreditsScene::onKeyReleased (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {

}

void CreditsScene::showMenu () {
    Director::getInstance ()->replaceScene (TransitionFade::create (1, MenuScene::createScene (), Color3B (0, 0, 0)));
}