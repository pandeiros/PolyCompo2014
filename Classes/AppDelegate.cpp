#include "AppDelegate.h"
#include "MenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        //glview = GLView::createWithFullScreen (mGameTitle);
        glview = GLView::createWithRect (mGameTitle, cocos2d::Rect (0.f, 0.f, mWidth, mHeight), 1.f);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats (IS_STATS_ACTIVE);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval (1.0 / FRAMERATE);

    // create a scene. it's an autorelease object
    mMenuScene = MenuScene::createScene ();

    // run
    director->runWithScene (mMenuScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
