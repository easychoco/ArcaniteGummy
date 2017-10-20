#include "DynamicGimmickChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

DynamicGimmickChild::DynamicGimmickChild(int _x, int _y, double _scale) :
DynamicGimmickChild(_x, _y, _scale, true)
{

}

DynamicGimmickChild::DynamicGimmickChild(int _x, int _y, double _scale, bool _isDeletable) : 
DynamicObject(_x, _y, (int)(32 * _scale), (int)(32 * _scale), 0, 0),
isDeletable(_isDeletable)
{
	dx = dy = 0;
	mDirection = false;
	scale = _scale;
	assert((_x + width / 2) % 32 == 0 && (_y + height / 2) % 32 == 0 && "DynamicGimmickÇÃç¿ïWÇ™ (32 * n + 16) Ç∂Ç·Ç»Ç¢Ç≈Ç∑");
}

DynamicGimmickChild::~DynamicGimmickChild()
{
	//DeleteGraphÇÕÇµÇ»Ç¢
}

//==============================================
//ì‡ïîprotectedä÷êî
//==============================================
void DynamicGimmickChild::standardMove(const StageChild* _stage)
{
	if (dx != 0 || dy != 0)
	{
		dx = getHorizontalDiffer(_stage, dx, dy < 0);
		dy = ((dy < 0) ? getTopDiffer(_stage, dy, dx < 0) : getBottomDiffer(_stage, dy, dx < 0));
	}

	this->p->raw_x += dx;
	this->p->raw_y += dy;
}


bool DynamicGimmickChild::rideOnGimmick(const Vector2* _player) const 
{
	/*
	return
		abs( p->y() - (_player->y() + PLAYER_CHIP_HEIGHT / 2) ) <= height * 2 / 3 &&
		abs( p->x() - _player->x() ) < width / 2;
	*/
	return abs((_player->raw_y + PLAYER_CHIP_HEIGHT_RATE() / 2) - this->getTopPosition()) <= 1000 && 
		abs(p->x() - _player->x()) < width / 2;
}

bool DynamicGimmickChild::standardOverLap(const Vector2* _player) const
{
	int half_w = this->width  * vectorRate / 2;
	int half_h = this->height * vectorRate / 2;

	return
		this->p->raw_x - half_w <= _player->raw_x &&
		this->p->raw_x + half_w >= _player->raw_x &&
		this->p->raw_y - half_h - dy - vectorRate <= _player->raw_y &&
		this->p->raw_y + half_h >= _player->raw_y;
}



int DynamicGimmickChild::getTopDiffer(const StageChild* _stage, const int _dy, bool _moveLeft) const { return DynamicObject::getTopDiffer(_stage, _dy, _moveLeft, false); }
int DynamicGimmickChild::getBottomDiffer(const StageChild* _stage, const int _dy, bool _moveLeft) const { return DynamicObject::getBottomDiffer(_stage, _dy, _moveLeft, false); }
int DynamicGimmickChild::getHorizontalDiffer(const StageChild* _stage, const int _dx, bool _moveUp) const { return DynamicObject::getHorizontalDiffer(_stage, _dx, _moveUp, false); }




}
}
}