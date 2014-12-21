#include "BodyCreator.h"

unsigned long BodyCreator::globalId = 0;
b2World * BodyCreator::world = new b2World(b2Vec2(0.f, 0.f));

BodyCreator::BodyCreator()
{
}


BodyCreator::~BodyCreator()
{
}


