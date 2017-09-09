#include "DynamicGimmickChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


DynamicGimmickChild::DynamicGimmickChild(int _x, int _y, double _scale) : 
DynamicObject(_x, _y, (int)(32 * _scale), (int)(32 * _scale), 0, 0)
{
	dx = dy = 0;
	mDirection = false;
	scale = _scale;
}

DynamicGimmickChild::~DynamicGimmickChild()
{

}

//==============================================
//“à•”protectedŠÖ”
//==============================================
void DynamicGimmickChild::standardMove(const Stage* _stage)
{
	this->p->raw_x += getHorizontalDiffer(_stage, dx);
	this->p->raw_y += ( (dy < 0) ? getTopDiffer(_stage, dy) : getTopDiffer(_stage, dy) );
}


bool DynamicGimmickChild::rideOnGimmick(const Vector2* _player) const 
{
	return abs( p->y() - (_player->y() + PLAYER_CHIP_HEIGHT / 2) ) < 10;
}

bool DynamicGimmickChild::standardOverLap(const Vector2* _player) const
{
	int tmp_w = this->width  * vectorRate / 2;
	int tmp_h = this->height * vectorRate / 2;

	return
		this->p->raw_x - tmp_w < _player->raw_x &&
		this->p->raw_x + tmp_w > _player->raw_x &&
		this->p->raw_y - tmp_h < _player->raw_y &&
		this->p->raw_y + tmp_h > _player->raw_y;
}



int DynamicGimmickChild::getTopDiffer(const Stage* _stage, const int dy) const { return DynamicObject::getTopDiffer(_stage, dy, false); }
int DynamicGimmickChild::getBottomDiffer(const Stage* _stage, const int dy) const { return DynamicObject::getBottomDiffer(_stage, dy, false); }
int DynamicGimmickChild::getHorizontalDiffer(const Stage* _stage, const int dx) const { return DynamicObject::getHorizontalDiffer(_stage, dx, false); }




}
}
}