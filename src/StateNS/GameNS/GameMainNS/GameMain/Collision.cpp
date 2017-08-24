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
		this->p->pos_x()			    < other->p->pos_x() + other->width  &&
		this->p->pos_x() + this->width  > other->p->pos_x()					&&
		this->p->pos_y()			    < other->p->pos_y() + other->height &&
		this->p->pos_y() + this->height > other->p->pos_y();
}


}
}
}