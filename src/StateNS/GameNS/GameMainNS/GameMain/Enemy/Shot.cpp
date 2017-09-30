#include "Shot.h"
#include "..\Character.h"
#include <cmath>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{



//graphは全てのShotで同じだからグローバル変数で
static int img = NULL;
static unsigned int black = GetColor(0, 0, 0);

//画像使用バージョン
Shot::Shot(const Character* parent, int _x, int _y, float _angle, float _speed, int _damage) :
Attack(parent, _x, _y, 15, 15)
{
	this->angle = pi(1 / 180.0f) * _angle;
	this->dx = (int)(_speed * cos(angle));
	this->dy = (int)(_speed * sin(angle));
	this->damageValue = _damage;

	initialize();
}


Shot::~Shot() 
{
	DeleteGraph(mImage);
}

void Shot::initialize()
{
	isActive = true;
	loadImage();
	assert(mImage != -1 && "Shot画像読み込みエラー!");
}

void Shot::update() 
{

	//画面外にあったらreturn
	if (!isActive)return;

	++time;

	//移動
	p->raw_x += dx;
	p->raw_y += dy;
}

void Shot::draw(const Vector2* _camera) const 
{
	//画面外にあったら描画なし
	if (!isActive)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true);
}

void Shot::setStatus_2args(Vector2 pos, int _angle, int _speed)
{
	this->isActive = true;
	if (pos != Vector2::ZERO)*p = pos;
	this->angle = pi(1 / 180.0f) * _angle;

	if (_speed != 0)
	{
		this->dx = (int)(_speed * cosf(angle));
		this->dy = (int)(_speed * sinf(angle));
	}
}

float sinf_degree(int degree) { return sinf(pi(degree / 180.0f)); }
float cosf_degree(int degree) { return cosf(pi(degree / 180.0f)); }


}
}
}