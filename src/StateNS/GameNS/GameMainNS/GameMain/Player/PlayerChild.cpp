#include "PlayerChild.h"
#include "..\Stage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

PlayerChild::PlayerChild(float _move, float _jump, int _jumpCount, int _hp) : Character(_hp),
maxMoveSpeed(_move),
maxJumpPower(_jump),
maxJumpCount(_jumpCount)
{
	this->moveSpeed = 0.0f;
	this->jumpPower = 0.0f;
	this->nowJumpCount = 0;
	this->prePush = false;
}

void PlayerChild::draw() const
{
	DrawFormatString(0, 60, MyData::WHITE, "Mokou");

	int draw_x = 320 + (p->pos_x - camera->pos_x) / MyData::vectorRate;
	int draw_y = 240 + (p->pos_y - camera->pos_y) / MyData::vectorRate;

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, img, true);
	DrawCircle(draw_x, draw_y, 5, MyData::GREEN, true);

	draw_other();
}


//================================================
//内部private関数
//================================================
void PlayerChild::standardMove(const Stage* _stage)
{
	move(_stage);
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
	if (Input_JUMP() && !prePush)jumpPower = maxJumpPower;

	//縦移動
	dy += gravity() - jump();

	dx = getHorizontalDiffer(_stage, dx);
	dy = getVerticalDiffer(_stage, dy);

	p->pos_x += dx;
	p->pos_y += dy;


	//カメラ位置を更新	
	*camera = Vector2(
		max(320, min(MyData::MAP_WIDTH  - 320, p->x())),
		max(240, min(MyData::MAP_HEIGHT - 240, p->y()))
	);
	
	prePush = Input_JUMP();
}


int PlayerChild::getHorizontalDiffer(const Stage* _stage, const int _dx) const
{
	//斜めブロックの場合はそのまま返す

	//チップの上半分の真ん中
	RawVector2 pos = RawVector2(p->pos_x, p->pos_y - MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (_stage->isSlant(chipType))return _dx;


	//チップの下半分の真ん中
	pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if(_stage->isSlant(chipType))return _dx;



	//通れないブロックならreturn 0

	//チップの真ん中
	pos = RawVector2(p->pos_x + _dx, p->pos_y);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//チップの上半分の真ん中
	pos = RawVector2(p->pos_x + _dx, p->pos_y - MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 + MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;
	

	//チップの下半分の真ん中
	pos = RawVector2(p->pos_x + _dx, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 - MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;

	return _dx;
}

int PlayerChild::getVerticalDiffer(const Stage* _stage, const int _dy) const
{
	//上方向
	if (jumpPower >= 0.5f)
	{
		//斜めブロックなら

		//チップの上端
		RawVector2 pos = RawVector2(p->x(), p->y() - MyData::PLAYER_CHIP_HEIGHT / 2);
		Stage::ChipType chipType = _stage->getChipType(pos);

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

		//チップの上半分の中心
		pos = RawVector2(p->x(), p->y() - MyData::PLAYER_CHIP_HEIGHT / 4);
		chipType = _stage->getChipType(pos);

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

		//チップの上端より少し上
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
	//ここまで上方向の判定



	//下方向
	//チップの最下端より少し上
	RawVector2 pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 - 1);
	Stage::ChipType	chipType= _stage->getChipType(pos / MyData::vectorRate);
	
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


	//チップの下半分の中心
	pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 4);
	chipType = _stage->getChipType(pos / MyData::vectorRate);

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



	//チップの最下端
	pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);

	//移動先が通れないブロックなら
	if (_stage->isRigid_down(chipType))
	{
		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	}

	return _dy;
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
	return 7 * MyData::vectorRate;
}


}
}
}