#include "PlayerChild.h"
#include "..\Stage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

PlayerChild::PlayerChild(float _move, float _jump) : 
maxMoveSpeed(_move),
maxJumpPower(_jump)
{
	this->moveSpeed = 0.0f;
	this->jumpPower = 0.0f;
	now_jumping = false;
}

void PlayerChild::standardMove(const Stage* _stage)
{
	move(_stage);

	//avoidSinking(_stage);
}

//移動
void PlayerChild::move(const Stage* _stage)
{
	int dx = 0;
	int dy = 0;

	//入力
	if (Input_RIGHT())dx += (int)(moveSpeed * MyData::vectorRate);
	if (Input_LEFT())dx -= (int)(moveSpeed * MyData::vectorRate);

	//ジャンプ
	if (Input_JUMP())jumpPower = maxJumpPower;

	//縦移動
	dy += gravity() - jump();

	p->pos_x += getHorizontalDiffer(_stage, dx);
	p->pos_y += getVerticalDiffer(_stage, dy);
}


int PlayerChild::getHorizontalDiffer(const Stage* _stage, int _dx) const
{
	//移動先のchipTypeをgetして...


	//斜めブロックの場合はそのまま返す
	RawVector2 pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate);
	if(_stage->isSlant(chipType))return _dx;


	pos = RawVector2(p->pos_x, p->pos_y - MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (_stage->isSlant(chipType))return _dx;
	


	//通れないブロックならreturn 0

	//チップの真ん中
	pos = RawVector2(p->pos_x + _dx, p->pos_y);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//チップの上
	pos = RawVector2(p->pos_x + _dx, p->pos_y - MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 + MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//チップの下
	pos = RawVector2(p->pos_x + _dx, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 - MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;

	return _dx;
}

int PlayerChild::getVerticalDiffer(const Stage* _stage, int _dy) const
{
	//上方向
	if (jumpPower >= 0.5f)
	{
		RawVector2 pos = RawVector2(p->x(), p->y() - MyData::PLAYER_CHIP_HEIGHT / 2);
		Stage::ChipType chipType = _stage->getChipType(pos);


		//斜めブロックなら
		if (chipType == _stage->TYPE_UP_SLANT_LEFT)
		{
			/* このブロック

			____
			\==|
			 \=|
			  \|

			*/

			int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - MyData::PLAYER_CHIP_HEIGHT - 1)) * MyData::vectorRate - MyData::PLAYER_CHIP_WIDTH_RATE() + p->pos_x % MyData::PLAYER_CHIP_WIDTH_RATE();
			if (pos.pos_y < 0)dy -= MyData::PLAYER_CHIP_HEIGHT_RATE() / 2;
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

			int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - MyData::PLAYER_CHIP_HEIGHT - 1)) * MyData::vectorRate - p->pos_x % MyData::PLAYER_CHIP_WIDTH_RATE();
			if (pos.pos_y < 0)dy -= MyData::PLAYER_CHIP_HEIGHT_RATE() / 2;
			return dy;
		}

		pos = RawVector2(p->x(), p->y() - MyData::PLAYER_CHIP_HEIGHT / 2 - 1);
			chipType = _stage->getChipType(pos);

		//移動先が通れないブロックなら
		if (_stage->isRigid_up(chipType))
		{
			int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - MyData::PLAYER_CHIP_HEIGHT)) * MyData::vectorRate;
	
			//天井に当たっている場合はfixToStageHeightの結果が少し変わるから調整
			if (pos.pos_y < 0)dy -= MyData::PLAYER_CHIP_HEIGHT_RATE() / 2;
			return dy;
		}


		return _dy;
	}

	//下方向
	RawVector2 pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 - 1);
	Stage::ChipType	chipType = _stage->getChipType(pos / MyData::vectorRate);

	//斜めブロックなら
	if (chipType == _stage->TYPE_DOWN_SLANT_LEFT)
	{
		/* このブロックなら

		|\
		|=\
		|==\

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2) + p->pos_x % MyData::CHIP_WIDTH_RATE();
	}
	if (chipType == _stage->TYPE_DOWN_SLANT_RIGHT)
	{
		/* このブロックなら

		  /|
		 /=|
		/==|

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2) + MyData::CHIP_WIDTH_RATE() - p->pos_x % MyData::CHIP_WIDTH_RATE();
	}

	pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);

	//移動先が通れないブロックなら
	if (_stage->isRigid_down(chipType))
	{
		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	}


	return _dy;
}


/*
//めり込み回避
void PlayerChild::avoidSinking(const Stage* _stage)
{
	//今の移動速度
	int moveDiffer = (int)moveSpeed + 1;

	Vector2 pos1;
	Vector2 pos2;

	Stage::ChipType chipType1;
	Stage::ChipType chipType2;

	//右キーが押されているときに読まれる
	if (Input_RIGHT())
	{
		//X軸右方向
		pos1 = Vector2(p->x() + moveDiffer, p->y() + MyData::PLAYER_CHIP_HEIGHT / 4);
		pos2 = Vector2(p->x() + moveDiffer, p->y() - MyData::PLAYER_CHIP_HEIGHT / 4);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//すり抜けられないなら位置を矯正
		if (_stage->isRigid(chipType1) || _stage->isRigid(chipType2))
		{
			p->pos_x = (p->x() / MyData::CHIP_WIDTH * MyData::CHIP_WIDTH + MyData::PLAYER_CHIP_WIDTH * 3 / 4) * MyData::vectorRate;
		}
	}

	//左キーが押されているときに読まれる
	else if (Input_LEFT())
	{
		//X軸左方向
		pos1 = Vector2(p->x() - moveDiffer, p->y() + MyData::PLAYER_CHIP_HEIGHT / 4);
		pos2 = Vector2(p->x() - moveDiffer, p->y() - MyData::PLAYER_CHIP_HEIGHT / 4);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//すり抜けられないなら位置を矯正
		if (_stage->isRigid(chipType1) || _stage->isRigid(chipType2))
		{
			p->pos_x = (p->x() / MyData::CHIP_WIDTH * MyData::CHIP_WIDTH + MyData::PLAYER_CHIP_WIDTH / 4) * MyData::vectorRate;
		}
	}

	//ジャンプ中に読まれる
	if (jumpPower >= 0.5f)
	{
		//Y軸上方向
		pos1 = Vector2(p->x() - moveDiffer, p->y() - MyData::PLAYER_CHIP_HEIGHT / 2);
		pos2 = Vector2(p->x() + moveDiffer, p->y() - MyData::PLAYER_CHIP_HEIGHT / 2);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//すり抜けられないなら位置を矯正
		if (_stage->isRigid(chipType1) && _stage->isRigid(chipType2))
		{
			p->pos_y = (p->y() / MyData::CHIP_HEIGHT * MyData::CHIP_HEIGHT + MyData::PLAYER_CHIP_HEIGHT  / 2) * MyData::vectorRate;
		}
	}
	else //ジャンプ中でないときに読まれる
	{
		//Y軸下方向
		pos1 = Vector2(p->x() - moveDiffer + 1, p->y() + MyData::PLAYER_CHIP_HEIGHT / 2);
		pos2 = Vector2(p->x() + moveDiffer - 1, p->y() + MyData::PLAYER_CHIP_HEIGHT / 2);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//上に乗れるブロックなら位置を矯正
		if (_stage->isRide(chipType1) && _stage->isRide(chipType2))
		{
			p->pos_y = (p->y() / MyData::CHIP_HEIGHT * MyData::CHIP_HEIGHT) * MyData::vectorRate;
		}
	}

	if (jumpPower <= 0.5f)
	{
		//斜めブロックに対する処理
		pos1 = Vector2(p->x(), p->y() + MyData::PLAYER_CHIP_HEIGHT / 2);
		pos2 = Vector2(p->x(), p->y() + MyData::PLAYER_CHIP_HEIGHT / 2 - 1);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		int s_dy = 0;

		if (_stage->isSlant(chipType1))
		{
			s_dy = (chipType1 == _stage->TYPE_SLANT_LEFT) ? p->x() % MyData::CHIP_HEIGHT : 32 - p->x() % MyData::CHIP_HEIGHT;
			p->pos_y = (p->y() / MyData::CHIP_HEIGHT * MyData::CHIP_HEIGHT + s_dy) * MyData::vectorRate;
		}
		else if (_stage->isSlant(chipType2))
		{
			p->pos_y -= gravity();
			s_dy = (chipType2 == _stage->TYPE_SLANT_LEFT) ? p->x() % MyData::CHIP_HEIGHT : 32 - p->x() % MyData::CHIP_HEIGHT;
			p->pos_y = (p->y() / MyData::CHIP_HEIGHT * MyData::CHIP_HEIGHT + s_dy) * MyData::vectorRate;
		}
	}

}
//*/

//ジャンプでの移動量を返す
//正の値で上方向
int PlayerChild::jump()
{
	jumpPower = max(0.0f, jumpPower - 1.0f);
	return (int)(jumpPower * MyData::vectorRate);
}

//かかる重力を返す
//正の値で下方向
int PlayerChild::gravity()
{
	//for Debug
	//このままいくならconstexprで
	return 5 * MyData::vectorRate;
}


}
}
}