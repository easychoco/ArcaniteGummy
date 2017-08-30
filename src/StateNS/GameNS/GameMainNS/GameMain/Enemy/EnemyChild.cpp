#include "Enemychild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

EnemyChild::EnemyChild(int _hp, int _x, int _y, int _w, int _h,float _jump,int _jumpCount) : Character(_hp, _x, _y, _w, _h,_jump,_jumpCount)
{
	initialize();
}

EnemyChild::~EnemyChild()
{

}

void EnemyChild::initialize()
{
	this->mTime = 0;
	this->isAlive = true;
	this->mDirection = false;
}

void EnemyChild::draw(const Vector2* _camera) const
{
	//‰æ–Ê“à‚É‚¢‚È‚¯‚ê‚Îreturn
	if (!isAlive)return;
	if (abs(p->pos_x() - _camera->pos_x()) > 350000 || abs(p->pos_y() - _camera->pos_y()) > 270000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();


	//•`‰æ
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, mDirection);
}

void EnemyChild::standardAction(const Stage* _stage)
{
	++mTime;
	checkIsAlive(_stage);
	if (!this->isAlive)return;

	processDamage();
	standardMove(_stage);
}


void EnemyChild::standardMove(const Stage* _stage)
{
	//‚â‚ç‚ê‚Ä‚¢‚é‚È‚çreturn
	if (!isAlive)return;

	int dx = next_dx;
	int dy = next_dy;

	next_dx = next_dy = 0;


	//ˆÚ“®
	//ˆø”‚ÍŽQÆ“n‚µ
	this->move(_stage, dx, dy);

	p->raw_x += dx;
	p->raw_y += dy;
}


void EnemyChild::checkIsAlive(const Stage* _stage)
{
	isAlive &= (this->hpController.getHP() > 0);
	isAlive &= (this->p->raw_y % MyData::MAP_HEIGHT_RATE() < (this->p->raw_y + 10000) % MyData::MAP_HEIGHT_RATE());
	isAlive &= (this->p->raw_y % MyData::MAP_HEIGHT_RATE() > (this->p->raw_y - 10000) % MyData::MAP_HEIGHT_RATE());
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