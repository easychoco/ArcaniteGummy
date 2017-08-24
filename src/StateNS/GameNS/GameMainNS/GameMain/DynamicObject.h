#pragma once

#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {

namespace GameMainNS{

class Collision;

class DynamicObject
{
public:
	DynamicObject(int x, int y, int w, int h);
	virtual ~DynamicObject();
	virtual void hittedAction() = 0;
	const Vector2* getVector2() const { return p; }
	bool isHit(const DynamicObject*) const;

	Vector2* p;
	Collision* collision;


private:
};




}
}
}