#pragma once

#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class DynamicObject;

class Collision
{
public:
	Collision(DynamicObject*, int w, int h);
	~Collision();
	bool isHit(const Collision* other) const;
	
	DynamicObject* parent;
	const Vector2* p;
	int width;
	int height;
};




}
}
}