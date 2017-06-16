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

	avoidSinking(_stage);
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

	//縦移動
	int nextX = max(0, min(MyData::MAP_WIDTH  * MyData::vectorRate, p->pos_x + dx)) / MyData::vectorRate;
	int nextY = max(0, min(MyData::MAP_HEIGHT * MyData::vectorRate, p->pos_y + dy)) / MyData::vectorRate;

	//移動先がいける場所なら の形式

	//X軸方向
	//次の行き先が通れるなら
	Stage::ChipType chipType = _stage->getChipType(Vector2(nextX, p->y()));
	if (!_stage->isRigid(chipType))
	{
		p->pos_x = nextX * MyData::vectorRate;
	}

	//Y軸方向
	chipType = _stage->getChipType(Vector2(p->x(), nextY));
	if (!_stage->isRigid(chipType))
	{
		p->pos_y = nextY * MyData::vectorRate;
	}
}

//めり込み回避
void PlayerChild::avoidSinking(const Stage* _stage)
{
	Vector2 pos1;
	Vector2 pos2;

	Stage::ChipType chipType1;
	Stage::ChipType chipType2;

	//ジャンプ中に読まれる
	if (jumpPower >= 0.5f)
	{
		//Y軸上方向
		Vector2 pos1 = Vector2(p->x() - MyData::PLAYER_CHIP_WIDTH / 4, p->y() - MyData::PLAYER_CHIP_HEIGHT / 2);
		Vector2 pos2 = Vector2(p->x() - MyData::PLAYER_CHIP_WIDTH / 4, p->y() - MyData::PLAYER_CHIP_HEIGHT / 2);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//すり抜けられないなら位置を矯正
		if (_stage->isRigid(chipType1) && _stage->isRigid(chipType2))
		{
			p->pos_y = (p->y() / MyData::PLAYER_CHIP_HEIGHT * MyData::PLAYER_CHIP_HEIGHT + MyData::PLAYER_CHIP_HEIGHT + 1) * MyData::vectorRate;
		}
	}
	else //ジャンプ中でないときに読まれる
	{
		//Y軸下方向
		pos1 = Vector2(p->x() - MyData::PLAYER_CHIP_WIDTH / 4, p->y() + MyData::PLAYER_CHIP_HEIGHT / 2);
		pos2 = Vector2(p->x() + MyData::PLAYER_CHIP_WIDTH / 4 - 1, p->y() + MyData::PLAYER_CHIP_HEIGHT / 2);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//上に乗れるブロックなら位置を矯正
		if (_stage->isRide(chipType1) || _stage->isRide(chipType2))
		{
			p->pos_y = (p->y() / MyData::PLAYER_CHIP_HEIGHT * MyData::PLAYER_CHIP_HEIGHT + MyData::PLAYER_CHIP_HEIGHT / 2) * MyData::vectorRate;
		}
	}

	//右キーが押されているときに読まれる
	if (Input_RIGHT())
	{
		//X軸右方向
		pos1 = Vector2(p->x() + MyData::PLAYER_CHIP_WIDTH / 4, p->y() + MyData::PLAYER_CHIP_HEIGHT / 4);
		pos2 = Vector2(p->x() + MyData::PLAYER_CHIP_WIDTH / 4, p->y() - MyData::PLAYER_CHIP_HEIGHT / 4);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//すり抜けられないなら位置を矯正
		if (_stage->isRigid(chipType1) && _stage->isRigid(chipType2))
		{
			p->pos_x = (p->x() / MyData::PLAYER_CHIP_WIDTH * MyData::PLAYER_CHIP_WIDTH + MyData::PLAYER_CHIP_WIDTH * 3 / 4) * MyData::vectorRate;
		}
	}

	//左キーが押されているときに読まれる
	else if (Input_LEFT())
	{
		//X軸左方向
		pos1 = Vector2(p->x() - MyData::PLAYER_CHIP_WIDTH / 4, p->y() + MyData::PLAYER_CHIP_HEIGHT / 4);
		pos2 = Vector2(p->x() - MyData::PLAYER_CHIP_WIDTH / 4, p->y() - MyData::PLAYER_CHIP_HEIGHT / 4);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//すり抜けられないなら位置を矯正
		if (_stage->isRigid(chipType1) && _stage->isRigid(chipType2))
		{
			p->pos_x = (p->x() / MyData::PLAYER_CHIP_WIDTH * MyData::PLAYER_CHIP_WIDTH + MyData::PLAYER_CHIP_WIDTH / 4) * MyData::vectorRate;
		}
	}

	//斜めブロックに対する処理
	pos1 = Vector2(p->x(), p->y() + MyData::PLAYER_CHIP_HEIGHT / 2 - 1);
	pos2 = Vector2(p->x(), p->y() + MyData::PLAYER_CHIP_HEIGHT / 4);

	chipType1 = _stage->getChipType(pos1);
	chipType2 = _stage->getChipType(pos2);

	if (_stage->isSlant(chipType1) || _stage->isSlant(chipType2))
	{
		p->pos_y -= ((p->x() % 32) * MyData::vectorRate);
	}
}

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