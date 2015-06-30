#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
{}

AnimatedSprite::~AnimatedSprite()
{}

AnimatedSprite* AnimatedSprite::create(std::string filename)
{
    AnimatedSprite *pSprite = new (std::nothrow) AnimatedSprite();
    if (pSprite && pSprite->init())
    {

        cocos2d::SpriteFrameCache * cache = cocos2d::SpriteFrameCache::getInstance();
        cache->addSpriteFramesWithFile(cocos2d::String::createWithFormat("anims/%s.plist", filename.c_str())->getCString());

        if (pSprite->initWithSpriteFrameName(cocos2d::String::createWithFormat("anims/%s_01.png", filename.c_str())->getCString()))
        {
            auto cache = cocos2d::AnimationCache::getInstance();
            cache->addAnimationsWithFile(cocos2d::String::createWithFormat("anims/%s.plist", filename.c_str())->getCString());
            pSprite->runAction(AnimationUtils::getAnimationRunningForever((filename + "_idle").c_str()));

            pSprite->autorelease();
            return pSprite;
        }
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}