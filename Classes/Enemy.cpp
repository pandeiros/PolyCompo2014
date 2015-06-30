#include "Enemy.h"

Enemy::Enemy()
{}

Enemy::~Enemy()
{}

Enemy* Enemy::create(cocos2d::Vec2 position, Enemies::Type type, Movement::Directions direction, b2World * world)
{
    Enemy* enemy = new Enemy();
    enemy->body = BodyCreator::createBody<Enemy>(Entities::ENEMY, BodyCreator::convertToBoxVec(position), enemy, world);
    enemy->type = Entities::ENEMY;

    std::string filename;

    switch (type)
    {
        case 0:
            filename = "sprites/TieFighter.png";
            break;
        default:
            filename = "sprites/TieFighter.png";
            break;
    }

    if (enemy->initWithFile(filename))
    {
        enemy->autorelease();

        enemy->initOptions(position);

        return enemy;
    }

    CC_SAFE_DELETE(enemy);
    return NULL;
}

void Enemy::update(float dt)
{
    body->SetLinearVelocity(BodyCreator::convertToBoxVec(cocos2d::Vec2(-Movement::enemySpeed * dt, 0)));

    if (this->getPosition().x > 3000 || this->getPosition().x < -1000)
    {
        this->isValid = false;
    }
}

void Enemy::initOptions(cocos2d::Vec2 position)
{
    this->setPosition(position);
}

bool Enemy::getIsValid()
{
    return isValid;
}

void Enemy::damage(Damage::Type type)
{
    hp -= type;
    if (hp <= 0)
    {
        this->die();
    }
}
