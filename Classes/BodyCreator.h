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

	struct bodyInfo {
		Entities::Type type;
		unsigned long id;
	};

	static b2Body* createBody(Entities::Type type, b2Vec2 position);

	static unsigned long globalId;

	static const unsigned int PixelPerMeter = 100;

	static b2World * world;

	static b2Vec2 convertToBoxVec(cocos2d::Vec2 vec) {
		return b2Vec2 (vec.x / PixelPerMeter, vec.y / PixelPerMeter);
	}

	static cocos2d::Vec2 convertToCocosVec(b2Vec2 vec) {
		return cocos2d::Vec2(vec.x * PixelPerMeter, vec.y * PixelPerMeter);
	}
};

#endif

