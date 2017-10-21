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
	void setSize(int w, int h);

	DynamicObject* parent = 0;
	const Vector2* p = 0;

	bool noCollide;
	bool calcFromCenter;

	int width;
	int height;

	int half_width;
	int half_height;

private:
};




}
}
}