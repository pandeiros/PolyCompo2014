#ifndef CONTACT_LISTENER
#define CONTACT_LISTENER

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Missile.h"

class ContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact)
    {

        void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
        void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserDataA && bodyUserDataB)
        {
            auto a = static_cast<Entity*>(bodyUserDataA);
            auto b = static_cast<Entity*>(bodyUserDataB);

            if (a->type == Entities::PLAYER || b->type == Entities::PLAYER)
            {
                if (a->type == Entities::PLAYER)
                {
                    if (b->type == Entities::ENEMY)
                    {
                        Player * player = static_cast<Player*>(bodyUserDataA);
                        player->damage(Damage::ENEMY_DMG);
                        Enemy * enemy = static_cast<Enemy*>(bodyUserDataB);
                        player->damage(Damage::FATAL);
                    }
                }
                else
                {
                    if (a->type == Entities::ENEMY)
                    {
                        Player * player = static_cast<Player*>(bodyUserDataB);
                        player->damage(Damage::ENEMY_DMG);
                        Enemy * enemy = static_cast<Enemy*>(bodyUserDataA);
                        player->damage(Damage::FATAL);
                    }
                }
            }
            else if (a->type == Entities::ENEMY || b->type == Entities::ENEMY)
            {

            }


        }

    }

    void EndContact(b2Contact* contact)
    {

        void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData)
        {
        }

        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData)
        {
        }

    }
};

#endif