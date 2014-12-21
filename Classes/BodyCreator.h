#ifndef BODYCREATOR
#define BODYCREATOR

#include "cocos2d.h"
#include "EnumIDs.h"
#include <Box2D\Box2D.h>

class BodyCreator
{
public:
    BodyCreator();
    ~BodyCreator();

    template <typename T>
    static b2Body* createBody (Entities::Type type, b2Vec2 position, T* entity, b2World * world);

    static unsigned long globalId;

    static float PixelPerMeter;

    static b2World * world;

    static b2Vec2 convertToBoxVec(cocos2d::Vec2 vec) {
        return b2Vec2 (vec.x / PixelPerMeter, vec.y / PixelPerMeter);
    }

    static cocos2d::Vec2 convertToCocosVec(b2Vec2 vec) {
        return cocos2d::Vec2(vec.x * PixelPerMeter, vec.y * PixelPerMeter);
    }
};

template <typename T>
b2Body* BodyCreator::createBody (Entities::Type type, b2Vec2 position, T* entity, b2World * world) {
    b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type = b2BodyType::b2_kinematicBody;

    b2Body * body = world->CreateBody (&bodyDef);

    body->SetUserData (entity);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 10.0;
    fixtureDef.isSensor = false;

    b2PolygonShape * polyShape;
    polyShape = new b2PolygonShape;

    switch (type) {
        case Entities::WATERBALL:

            break;
        case Entities::FIREBALL:

            break;
        case Entities::PLAYER:
            polyShape->SetAsBox (115.f / 2.f / PixelPerMeter, 138.f / 2.f / PixelPerMeter);
            break;
        case Entities::ENEMY:
            polyShape->SetAsBox (112.f / 2.f / PixelPerMeter, 55.f / 2.f / PixelPerMeter);
            break;
        case Entities::DART:

            break;
    }

    fixtureDef.shape = polyShape;
    body->CreateFixture (&fixtureDef);

    return body;

}

#endif

