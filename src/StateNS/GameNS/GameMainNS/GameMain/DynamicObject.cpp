#include "DynamicObject.h"


#include "Collision.h"
#include "Stage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


DynamicObject::DynamicObject(int _x, int _y, int _w, int _h, float _jump,int _jumpCount):
maxJumpPower(_jump),
maxJumpCount(_jumpCount)
{
	p = new Vector2(_x, _y);
	collision = new Collision(this, _w, _h);
	this->width = _w;
	this->height = _h;
	jumpPower = 0;
	nowJumpCount = 0;
}

DynamicObject::~DynamicObject()
{
	SAFE_DELETE(p);
	SAFE_DELETE(collision);
}

bool DynamicObject::isHit(const DynamicObject* _other) const
{
	return this->collision->isHit(_other->collision);
}


//for Debug
int DynamicObject::getColliX() const
{
	return collision->p->raw_x;
}

//for Debug
int DynamicObject::getColliY() const
{
	return collision->p->raw_y;
}


//==============================================
//内部protected関数
//==============================================
//cameraを中心とした描画
void DynamicObject::standardDraw(const Vector2* _camera, const Vector2* _pos, const int& _image, const bool& _direction) const
{

	//TODO 引数の const Vector2* _pos っていらねーじゃん
	/*
	if (//同じステージにいなければreturn
		_pos->raw_x / MAP_WIDTH_RATE() != _camera->raw_x / MAP_WIDTH_RATE() ||
		_pos->raw_y / MAP_HEIGHT_RATE() != _camera->raw_y / MAP_HEIGHT_RATE()
		)
		return;
	//*/
	
	//画面内にいなければreturn
	if (abs(p->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, _image, true, _direction);
}

//cameraを中心とした描画 scaleありバージョン
void DynamicObject::standardDraw(const Vector2* _camera, const Vector2* _pos, const double& scale, const int& _image, const bool& _direction) const
{
	/*
	if (//同じステージにいなければreturn
		_pos->raw_x / MAP_WIDTH_RATE() != _camera->raw_x / MAP_WIDTH_RATE() ||
		_pos->raw_y / MAP_HEIGHT_RATE() != _camera->raw_y / MAP_HEIGHT_RATE()
	)
	return;
	//*/

	//画面内にいなければreturn
	if (abs(_pos->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y, scale, 0.0, _image, true, _direction);
}


//==============================================
//移動関連
//==============================================
//ジャンプでの移動量を返す
//正の値で上方向
int DynamicObject::jump()
{
	jumpPower = max(0.0f, jumpPower - 1.0f);
	return (int)(jumpPower * MyData::vectorRate);
}

//かかる重力を返す
//正の値で下方向
int DynamicObject::gravity()
{
	//for Debug
	//このままいくならconstexprで
	return 7 * MyData::vectorRate;
}

int DynamicObject::getTopDiffer(const Stage* _stage, const int _dy, bool _isPlayer) const
{
	//斜めブロックなら

	//チップの上端
	RawVector2 pos = RawVector2(p->x(), p->y() - height / 2);
	Stage::ChipType chipType = _stage->getChipType(pos, _isPlayer);

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
	chipType = _stage->getChipType(pos, _isPlayer);

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
	chipType = _stage->getChipType(pos, _isPlayer);

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


//========================================================================
// 内部protected関数
//========================================================================
int DynamicObject::getBottomDiffer(const Stage* _stage, const int _dy, bool _isPlayer) const
{
	//下方向
	//チップの最下端より少し上
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() + (height * vectorRate) / 2 - 1);
	Stage::ChipType	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);

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
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);

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
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * vectorRate) / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);

	//TODO 
	//_stage->getTopPositionは高速化できる

	//移動した先のチップの最下端
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * vectorRate) / 2 + _dy);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);

	//移動先が通れないブロックなら
	if (_stage->isRigid_down(chipType))
	{
		const int quart_height = PLAYER_CHIP_HEIGHT_RATE() / 4;
		int differ = _stage->getTopPosition(p, quart_height * 3) - fixToVectorHeight(p->pos_y() + quart_height * 3);
		differ %= (quart_height * 2);
		return fixToVectorHeight(p->pos_y() + quart_height) - p->pos_y() + differ;
	}

	return _dy;
}

int DynamicObject::getHorizontalDiffer(const Stage* _stage, const int _dx, bool _isPlayer) const
{
	//斜めブロックの場合はそのまま返す

	//チップの上半分の真ん中
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() - (height * MyData::vectorRate) / 2);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (_stage->isSlant(chipType))return _dx;


	//チップの下半分の真ん中
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * MyData::vectorRate) / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (_stage->isSlant(chipType))return _dx;


	//通れないブロックならreturn 0

	//チップの真ん中
	pos = RawVector2(p->pos_x() + _dx, p->pos_y());
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//チップの上半分の真ん中
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() - (height * MyData::vectorRate) / 2 + MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//チップの下半分の真ん中
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() + (height * MyData::vectorRate) / 2 - MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (chipType == _stage->TYPE_RIGID)return 0;

	return _dx;
}


//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}