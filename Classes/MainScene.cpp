#include "MainScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    mEventListener = cocos2d::EventListenerKeyboard::create();
    mEventListener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
    mEventListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mEventListener, this);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    return true;
}

void MainScene::update(float dt)
{

}


void MainScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox ("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit (0);
#endif
}
