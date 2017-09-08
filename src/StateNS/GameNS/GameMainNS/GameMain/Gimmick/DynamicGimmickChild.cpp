#include "DynamicGimmickChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


DynamicGimmickChild::DynamicGimmickChild(int _x, int _y, double _scale) : 
DynamicObject(_x, _y, (int)(32 * _scale), (int)(32 * _scale), 0, 0)
{
	scale = _scale;
	mDirection = false;
}

DynamicGimmickChild::~DynamicGimmickChild()
{

}

//==============================================
//内部プライベート関数
//==============================================
int DynamicGimmickChild::getTopDiffer(const Stage* _stage, const int dy) const { return DynamicObject::getTopDiffer(_stage, dy, false); }
int DynamicGimmickChild::getBottomDiffer(const Stage* _stage, const int dy) const { return DynamicObject::getBottomDiffer(_stage, dy, false); }
int DynamicGimmickChild::getHorizontalDiffer(const Stage* _stage, const int dx) const { return DynamicObject::getHorizontalDiffer(_stage, dx, false); }




}
}
}