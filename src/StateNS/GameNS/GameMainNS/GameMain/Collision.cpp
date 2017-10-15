#include "Collision.h"
#include "DynamicObject.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Collision::Collision(DynamicObject* _parent, int _w, int _h) :
parent(_parent)
{
	this->p = _parent->getVector2();
	this->noCollide = false;
	this->setSize(_w, _h);
}

Collision::~Collision()
{
	//‚±‚±‚Å‚Ídelete‚µ‚È‚¢
	this->parent = 0;
	this->p = 0;
}

void Collision::setSize(int _w, int _h)
{
	this->width  = _w * vectorRate;
	this->height = _h * vectorRate;

	this->half_width  = this->width / 2;
	this->half_height = this->height / 2;
}

bool Collision::isHit(const Collision* other) const
{
	if (noCollide)return false;
	return
		this->p->raw_x - this->half_width  < other->p->raw_x + other->half_width  &&
		this->p->raw_x + this->half_width  > other->p->raw_x - other->half_width  &&
		this->p->raw_y - this->half_height < other->p->raw_y + other->half_height &&
		this->p->raw_y + this->half_height > other->p->raw_y - other->half_height;
}


}
}
}