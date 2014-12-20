#include "MainScene.h"

USING_NS_CC;

Scene* MainScene::createScene () {
    // 'scene' is an autorelease object
    auto scene = Scene::create ();

    // 'layer' is an autorelease object
    auto layer = MainScene::create ();

    // add layer as a child to scene
    scene->addChild (layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init () {
    //////////////////////////////
    // 1. super init first
    if (!Layer::init ()) {
        return false;
    }
    
    mEventListener = cocos2d::EventListenerKeyboard::create ();
    mEventListener->onKeyPressed = CC_CALLBACK_2 (MainScene::onKeyPressed, this);
    mEventListener->onKeyReleased = CC_CALLBACK_2 (MainScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority (mEventListener, this);

    Size visibleSize = Director::getInstance ()->getVisibleSize ();
    Vec2 origin = Director::getInstance ()->getVisibleOrigin ();

    ///////////////////////////////
    //// 2. add a menu item with "X" image, which is clicked to quit the program
    ////    you may modify it.

    //// add a "close" icon to exit the progress. it's an autorelease object
    //auto closeItem = MenuItemImage::create (
    //    "CloseNormal.png",
    //    "CloseSelected.png",
    //    CC_CALLBACK_1 (MainScene::menuCloseCallback, this));

    //closeItem->setPosition (Vec2 (origin.x + visibleSize.width - closeItem->getContentSize ().width / 2,
    //    origin.y + closeItem->getContentSize ().height / 2));

    //// create menu, it's an autorelease object
    //auto menu = Menu::create (closeItem, NULL);
    //menu->setPosition (Vec2::ZERO);
    //this->addChild (menu, 1);

    ///////////////////////////////
    //// 3. add your codes below...

    //// add a label shows "Hello World"
    //// create and initialize a label

    //auto label = LabelTTF::create ("Hello World", "Arial", 24);

    //// position the label on the center of the screen
    //label->setPosition (Vec2 (origin.x + visibleSize.width / 2,
    //    origin.y + visibleSize.height - label->getContentSize ().height));

    //// add the label as a child to this layer
    //this->addChild (label, 1);

    // add "HelloWorld" splash screen"
    //testSprite = Sprite::create ("HelloWorld.png");

    // position the sprite on the center of the screen
    //testSprite->setPosition (Vec2 (visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // add the sprite as a child to this layer
   // this->addChild (testSprite, 0);

    // HERE STARTS THE MAGIC
    //scheduleUpdate ();
   
    //mEventListener->onKeyPressed = CC_CALLBACK_2 (MainScene::onKeyPressed, this);

    return true;
}

// Update
void MainScene::update (float dt) {
   
}
//
//void MainScene::onKeyPressed (cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
//    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
//        Director::getInstance ()->end ();
//}


void MainScene::menuCloseCallback (Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox ("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif

    Director::getInstance ()->end ();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit (0);
#endif
}
