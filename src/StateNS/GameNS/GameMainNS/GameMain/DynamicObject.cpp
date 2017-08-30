#include "DynamicObject.h"


#include "Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


DynamicObject::DynamicObject(int _x, int _y, int _w, int _h,float _jump,int _jumpCount):
	maxJumpPower(_jump),
	maxJumpCount(_jumpCount)
{
	p = new Vector2(_x, _y);
	collision = new Collision(this, _w, _h);
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

	if (//同じステージにいなければreturn
		_pos->raw_x / MAP_WIDTH_RATE() != _camera->raw_x / MAP_WIDTH_RATE() ||
		_pos->raw_y / MAP_HEIGHT_RATE() != _camera->raw_y / MAP_HEIGHT_RATE()
		)
	return;

	//画面内にいなければreturn
	if (abs(_pos->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, _image, true, _direction);
}


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


//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}