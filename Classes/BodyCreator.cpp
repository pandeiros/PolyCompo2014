#include "BodyCreator.h"

unsigned long BodyCreator::globalId = 0;
b2World * BodyCreator::world = new b2World(b2Vec2(0.f, 0.f));

BodyCreator::BodyCreator()
{
}


BodyCreator::~BodyCreator()
{
}

b2Body* BodyCreator::createBody(Entities::Type type, b2Vec2 position) {
	b2BodyDef bodyDef;
	bodyDef.position = position;
	bodyDef.type = b2BodyType::b2_dynamicBody;

	b2Body * body = world->CreateBody(&bodyDef);

	bodyInfo * info = new bodyInfo;
	info->id = globalId;
	info->type = type;
	body->SetUserData(info);

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0;
	fixtureDef.friction = 0.0;

	b2PolygonShape * polyShape;
	polyShape = new b2PolygonShape;

	switch (type) {
		case Entities::PLAYER_PROJECTTILE:

			break;
		case Entities::PLAYER:
			polyShape->SetAsBox(115.f/2/PixelPerMeter,138.f/2/PixelPerMeter);
			break;
		case Entities::ENEMY:
			polyShape->SetAsBox(112.f / 2 / PixelPerMeter, 55.f / 2 / PixelPerMeter);
			break;
		case Entities::ENEMY_PROJECTTILE:

			break;
	}
	//polyShape->SetAsBox

	fixtureDef.shape = polyShape;
	body->CreateFixture(&fixtureDef);

	return body;

}
