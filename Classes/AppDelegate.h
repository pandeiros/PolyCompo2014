#ifndef  APP_DELEGATE
#define  APP_DELEGATE

#include "cocos2d.h"

#define IS_STATS_ACTIVE false
#define FRAMERATE 60
/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

private:
    // Game title
    std::string mGameTitle = "If You Want Pisces, Prepare For War!";

    // Scenes
    cocos2d::Scene * mMenuScene;

    float mWidth = 1366;
    float mHeight = 768;
};

#endif // _APP_DELEGATE_H_

