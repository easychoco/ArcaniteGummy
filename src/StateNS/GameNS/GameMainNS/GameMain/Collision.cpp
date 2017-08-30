#include "Collision.h"
#include "DynamicObject.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Collision::Collision(DynamicObject* _parent, int _w, int _h) :
parent(_parent)
{
	this->p = _parent->getVector2();
	this->width = _w * MyData::vectorRate;
	this->height = _h * MyData::vectorRate;
}

Collision::~Collision()
{
	parent = 0;
	p = 0;
}

bool Collision::isHit(const Collision* other) const
{
	return
		this->p->raw_x			      < other->p->raw_x + other->width  &&
		this->p->raw_x + this->width  > other->p->raw_x					&&
		this->p->raw_y			      < other->p->raw_y + other->height &&
		this->p->raw_y + this->height > other->p->raw_y;
}


}
}
}