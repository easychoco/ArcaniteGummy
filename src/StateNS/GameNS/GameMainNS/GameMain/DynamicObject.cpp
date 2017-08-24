#include "DynamicObject.h"


#include "Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


DynamicObject::DynamicObject(int _x, int _y, int _w, int _h)
{
	p = new Vector2(_x, _y);
	collision = new Collision(this, _w, _h);
}

DynamicObject::~DynamicObject()
{
	SAFE_DELETE(p);
	SAFE_DELETE(collision);
}

bool DynamicObject::isHit(const DynamicObject* _other) const
{
	return this->collision->isHit(_other->collision);
}



//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}