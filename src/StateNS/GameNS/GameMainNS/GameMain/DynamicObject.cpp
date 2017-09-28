#include "DynamicObject.h"


#include "Collision.h"
#include "Stages\StageChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

DynamicObject::DynamicObject(int x, int y, int w, int h, float jump, int jumpCount) :
DynamicObject(x, y, w, h, jump, jumpCount, false)
{ }

DynamicObject::DynamicObject(int _x, int _y, int _w, int _h, float _jump,int _jumpCount, bool _hasChild):
maxJumpPower(_jump),
maxJumpCount(_jumpCount),
hasChild(_hasChild)
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
void DynamicObject::standardDraw(const Vector2* _camera, const int& _image, const bool& _direction) const
{

	//画面内にいなければreturn
	if (abs(p->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, _image, true, _direction);
}

//cameraを中心とした描画 scaleありバージョン
void DynamicObject::standardDraw(const Vector2* _camera, const double& scale, const int& _image, const bool& _direction) const
{

	//画面内にいなければreturn
	if (abs(p->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

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

int DynamicObject::getTopDiffer(const StageChild* _stage, const int _dy, bool _moveLeft, bool _isPlayer) const
{
	//widthが32じゃなかったら，その分ずらして計算する必要がある
	int extraDiffer = (width - CHIP_WIDTH) / 2;
	if (_moveLeft)extraDiffer *= -1;

	//斜めブロックなら

	//チップの上端
	RawVector2 pos = RawVector2(p->x() + extraDiffer, p->y() - height / 2);
	StageChild::ChipType chipType = _stage->getChipType(pos, _isPlayer);

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
	pos = RawVector2(p->x() + extraDiffer, p->y() - height / 4);
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

	//斜めじゃないチップに対して

	//移動した先のチップタイプを取得
	pos = RawVector2(p->pos_x() + extraDiffer, p->pos_y() - (height * vectorRate) / 2 + _dy);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);

	//移動先が通れないブロックなら
	if (_stage->isRigid_up(chipType))
	{
		const int half_height = (height * vectorRate) / 2;
		return _stage->getBottomPosition(p, -half_height + _dy) - (p->pos_y() - half_height);
	}

	return _dy;
}


//========================================================================
// 内部protected関数
//========================================================================
int DynamicObject::getBottomDiffer(const StageChild* _stage, const int _dy, bool _moveLeft, bool _isPlayer) const
{
	//widthが32じゃなかったら，その分ずらして計算する必要がある
	int extraDiffer = vectorRate * (width - CHIP_WIDTH) / 2;
	if(_moveLeft)extraDiffer *= -1;

	//下方向
	//チップの最下端より少し上
	RawVector2 pos = RawVector2(p->pos_x() + extraDiffer, p->pos_y() + (height * vectorRate) / 2 - 1);
	StageChild::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (this->onRigidBlock())chipType = StageChild::ChipType::TYPE_RIGID;

	//斜めブロックなら
	if (chipType == _stage->TYPE_DOWN_SLANT_LEFT)
	{
		/* このブロックなら

		|\
		|=\
		|==\

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + (height * vectorRate) / 2) + p->pos_x() % CHIP_WIDTH_RATE();
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
	pos = RawVector2(p->pos_x() + extraDiffer, p->pos_y() + (height * MyData::vectorRate) / 4);
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

	//斜めじゃないチップに対して

	//TODO 
	//_stage->getTopPositionは高速化できる

	//移動した先のチップタイプを取得
	pos = RawVector2(p->pos_x() + extraDiffer, p->pos_y() + (height * vectorRate) / 2 + _dy);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (this->onRigidBlock())chipType = StageChild::ChipType::TYPE_RIGID;

	//移動先が通れないブロックなら
	if (_stage->isRigid_down(chipType))
	{
		const int half_height = (height * vectorRate) / 2;
		return _stage->getTopPosition(p, half_height + _dy) - (p->pos_y() + half_height);
		/*
		旧式
		int differ = _stage->getTopPosition(p, half_height + _dy) - fixToVectorHeight(p->pos_y() + half_height + _dy);
		differ %= half_height;
		return fixToVectorHeight(p->pos_y() + half_height + _dy) - (p->pos_y() + half_height) + differ;
		*/
	}
	
	return _dy;
}

int DynamicObject::getHorizontalDiffer(const StageChild* _stage, const int _dx, bool _moveUp, bool _isPlayer) const
{
	//斜めブロックの場合はそのまま返す

	//チップの上半分の真ん中
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() - (height * MyData::vectorRate) / 4);
	StageChild::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (_stage->isSlant(chipType))return _dx;


	//チップの下半分の真ん中
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * MyData::vectorRate) / 4);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (_stage->isSlant(chipType))return _dx;


	//通れないブロックならreturn 0

	//チップの真ん中
	pos = RawVector2(p->pos_x() + _dx, p->pos_y());
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//チップの上半分の真ん中
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() - (height * MyData::vectorRate) / 4);//2 + MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//チップの下半分の真ん中
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() + (height * MyData::vectorRate) / 4);// 2 - MyData::vectorRate);
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