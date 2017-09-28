#include "Enemychild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

EnemyChild::EnemyChild(int hp, int x, int y, int w, int h) :
EnemyChild(hp, x, y, w, h, false)
{ }

EnemyChild::EnemyChild(int _hp, int _x, int _y, int _w, int _h, bool _hasChild) : 
Character(_hp, _x, _y, _w, _h, false, 0, 0, _hasChild)
{
	initialize();
}

EnemyChild::~EnemyChild()
{

}

void EnemyChild::initialize()
{
	this->mIsAlive = true;
	this->mDirection = false;
}

void EnemyChild::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (!mIsAlive)return;
	
	standardDraw(_camera, mImage, mDirection);
	draw_other(_camera);
}

void EnemyChild::standardAction(const StageChild* _stage)
{
	checkIsAlive(_stage);
	if (!this->mIsAlive)return;

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