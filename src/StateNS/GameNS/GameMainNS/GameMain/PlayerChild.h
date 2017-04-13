#pragma once

#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class PlayerChild
{
public:
	virtual ~PlayerChild() {};
	virtual PlayerChild* update() = 0;
	virtual void draw() const = 0;
	const Vector2* getVector2() const { return p; }

protected:
	Vector2* p;
};




}
}
}