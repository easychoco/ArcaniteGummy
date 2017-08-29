#include "Character.h"
#include "Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Character::Character(int _hp, int _x, int _y, int _w, int _h) : 
DynamicObject(_x, _y, _w, _h),
hpController(HPController(this, _hp))
{
	width = _w;
	height = _h;
	next_dx = next_dy = 0;

	damaged = false;
	damagedTime = 0;
}

Character::~Character()
{

}

//キャラをdx, dyだけ移動させる
void Character::moveCharacter(float _dx, float _dy)
{
	this->next_dx += (int)(_dx * MyData::vectorRate);
	this->next_dy += (int)(_dy * MyData::vectorRate);
}

//キャラをx, yの位置に移動させる
void Character::arrangeCharacter(float _x, float _y)
{
	p->raw_x = (int)(_x * MyData::vectorRate);
	p->raw_y = (int)(_y * MyData::vectorRate);
}


int Character::getTopDiffer(const Stage* _stage, const int _dy) const
{
	//斜めブロックなら

	//チップの上端
	RawVector2 pos = RawVector2(p->x(), p->y() - height / 2);
	Stage::ChipType chipType = _stage->getChipType(pos);

	if (chipType == _stage->TYPE_UP_SLANT_LEFT)
	{
		/* このブロック

		____
		\==|
		 \=|
		  \|

		*/

		int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - height - 1)) * MyData::vectorRate - (width * MyData::vectorRate) + p->pos_x() % (width * MyData::vectorRate);
		if (pos.pos_y < 0)dy -= (height * MyData::vectorRate) / 2;
		return dy;
	}
	if (chipType == _stage->TYPE_UP_SLANT_RIGHT)
	{
		/* このブロック

		_____
		|==/
		|=/
		|/

		*/

		int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - height - 1)) * MyData::vectorRate - p->pos_x() % (width * MyData::vectorRate);
		if (pos.pos_y < 0)dy -= (height * MyData::vectorRate) / 2;
		return dy;
	}

	//チップの上半分の中心
	pos = RawVector2(p->x(), p->y() - height / 4);
	chipType = _stage->getChipType(pos);

	if (chipType == _stage->TYPE_UP_SLANT_LEFT)
	{
		/* このブロック

		____
		\==|
		 \=|
		  \|

		*/

		int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - height - 1)) * MyData::vectorRate - (width * MyData::vectorRate) + p->pos_x() % (width * MyData::vectorRate);
		if (pos.pos_y < 0)dy -= (height * MyData::vectorRate) / 2;
		return dy;
	}
	if (chipType == _stage->TYPE_UP_SLANT_RIGHT)
	{
		/* このブロック

		_____
		|==/
		|=/
		|/

		*/

		int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - height - 1)) * MyData::vectorRate - p->pos_x() % (width * MyData::vectorRate);
		if (pos.pos_y < 0)dy -= (height * MyData::vectorRate) / 2;
		return dy;
	}

	//チップの上端より少し上
	pos = RawVector2(p->x(), p->y() - height / 2 - 1);
	chipType = _stage->getChipType(pos);

	//移動先が通れないブロックなら
	if (_stage->isRigid_up(chipType))
	{
		int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - height)) * MyData::vectorRate;

		//天井に当たっている場合はfixToStageHeightの結果が少し変わるから調整
		if (pos.pos_y < 0)dy -= (height * MyData::vectorRate) / 2;
		return dy;
	}

	return _dy;
}

int Character::getBottomDiffer(const Stage* _stage, const int _dy) const
{
	//下方向
	//チップの最下端より少し上
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() + (height * MyData::vectorRate) / 2 - 1);
	Stage::ChipType	chipType = _stage->getChipType(pos / MyData::vectorRate);

	//斜めブロックなら
	if (chipType == _stage->TYPE_DOWN_SLANT_LEFT)
	{
		/* このブロックなら

		|\
		|=\
		|==\

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + (height * MyData::vectorRate) / 2) + p->pos_x() % MyData::CHIP_WIDTH_RATE();
	}

	if (chipType == _stage->TYPE_DOWN_SLANT_RIGHT)
	{
		/* このブロックなら

		  /|
		 /=|
		/==|

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + (height * MyData::vectorRate) / 2) + MyData::CHIP_WIDTH_RATE() - p->pos_x() % MyData::CHIP_WIDTH_RATE();
	}


	//チップの下半分の中心
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * MyData::vectorRate) / 4);
	chipType = _stage->getChipType(pos / MyData::vectorRate);

	//斜めブロックなら
	if (chipType == _stage->TYPE_DOWN_SLANT_LEFT)
	{
		/* このブロックなら

		|\
		|=\
		|==\

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + (height * MyData::vectorRate) / 2) + p->pos_x() % MyData::CHIP_WIDTH_RATE();
	}

	if (chipType == _stage->TYPE_DOWN_SLANT_RIGHT)
	{
		/* このブロックなら

		  /|
		 /=|
		/==|

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + (height * MyData::vectorRate) / 2) + MyData::CHIP_WIDTH_RATE() - p->pos_x() % MyData::CHIP_WIDTH_RATE();
	}



	//チップの最下端
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * MyData::vectorRate) / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);

	//移動先が通れないブロックなら
	if (_stage->isRigid_down(chipType))
	{
		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + (height * MyData::vectorRate) / 2);
	}

	return _dy;
}

int Character::getHorizontalDiffer(const Stage* _stage, const int _dx) const
{
	//斜めブロックの場合はそのまま返す

	//チップの上半分の真ん中
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() - (height * MyData::vectorRate) / 2);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (_stage->isSlant(chipType))return _dx;


	//チップの下半分の真ん中
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * MyData::vectorRate) / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (_stage->isSlant(chipType))return _dx;



	//通れないブロックならreturn 0

	//チップの真ん中
	pos = RawVector2(p->pos_x() + _dx, p->pos_y());
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//チップの上半分の真ん中
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() - (height * MyData::vectorRate) / 2 + MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//チップの下半分の真ん中
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() + (height * MyData::vectorRate) / 2 - MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;

	return _dx;
}

}
}
}