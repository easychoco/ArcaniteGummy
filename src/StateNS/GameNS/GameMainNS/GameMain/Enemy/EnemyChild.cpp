#include "Enemychild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

EnemyChild::EnemyChild(int hp, int x, int y, int w, int h) :
EnemyChild(hp, x, y, w, h, false, false)
{ }

EnemyChild::EnemyChild(int _hp, int _x, int _y, int _w, int _h, bool _hasChild, bool _isBoss) : 
Character(_hp, _x, _y, _w, _h, false, 0, 0, _hasChild),
isBoss(_isBoss)
{
	initialize();
}

EnemyChild::~EnemyChild()
{
	DeleteGraph(mImage);
}

void EnemyChild::initialize()
{
	this->mIsAlive = true;
	this->mIsActive = false;
	this->mDirection = false;
	this->actState = ENE_ACT_NONE;
	this->aTime = 0;
}

void EnemyChild::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (!mIsAlive)return;

	checkIsActive(_camera);
	if (!mIsActive)return;
		
	standardDraw(_camera,mDirection);
	draw_other(_camera);
}

void EnemyChild::standardDraw(const Vector2* _camera, const bool& _direction) const
{
	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	//DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage[actState * 2 + (aTime / 10) % 2], true, _direction);
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, _direction);
}

void EnemyChild::standardAction(const StageChild* _stage)
{
	checkIsAlive(_stage);
	if (!this->mIsAlive || !this->mIsActive)return;

	processDamage();
	standardMove(_stage);
}

void EnemyChild::standardMove(const StageChild* _stage)
{
	//やられているならreturn
	if (!mIsAlive)return;

	int dx = next_dx;
	int dy = next_dy;

	next_dx = next_dy = 0;


	//移動
	//引数は参照渡し
	this->move(_stage, dx, dy);

	p->raw_x += dx;
	p->raw_y += dy;
}

void EnemyChild::checkIsAlive(const StageChild* _stage)
{
	//HPが0ならfalse
	mIsAlive &= (this->hpController.getHP() > 0);

	//マップ外ならfalse
	mIsAlive &= (this->p->raw_y % MAP_HEIGHT_RATE() < (this->p->raw_y + 10000) % MAP_HEIGHT_RATE());
	mIsAlive &= (this->p->raw_y % MAP_HEIGHT_RATE() > (this->p->raw_y - 10000) % MAP_HEIGHT_RATE());
}

void EnemyChild::checkIsActive(const Vector2* _camera) const 
{
	//画面内にいなければfalse
	this->mIsActive = (abs(p->raw_x - _camera->raw_x) < 480000 && abs(p->raw_y - _camera->raw_y) < 320000);
}

void EnemyChild::processDamage()
{
	if (damaged)
	{
		++damagedTime;
		if (damagedTime < 3)hittedAction();
		if (damagedTime > 60)
		{
			damaged = false;
			damagedTime = 0;
		}
	}
}



}
}
}