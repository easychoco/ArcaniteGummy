#include "BossChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

BossChild::BossChild(int _hp, int _x, int _y, int _w, int _h,float _jump,int _jumpCount) : Character(_hp, _x, _y, _w, _h,_jump,_jumpCount)
{
	initialize();
}

BossChild::~BossChild()
{

}

void BossChild::initialize()
{
	this->mTime = 0;
	this->mIsAlive = true;
	this->mDirection = false;
}

void BossChild::draw(const Vector2* _camera) const
{
	//‰æ–Ê“à‚É‚¢‚È‚¯‚ê‚Îreturn
	if (!mIsAlive)return;
	
	standardDraw(_camera, p, mImage, mDirection);
}

void BossChild::standardAction(const Stage* _stage)
{
	++mTime;
	checkIsAlive(_stage);
	if (!this->mIsAlive)return;

	processDamage();
	standardMove(_stage);
}


void BossChild::standardMove(const Stage* _stage)
{
	//‚â‚ç‚ê‚Ä‚¢‚é‚È‚çreturn
	if (!mIsAlive)return;

	int dx = next_dx;
	int dy = next_dy;

	next_dx = next_dy = 0;


	//ˆÚ“®
	//ˆø”‚ÍŽQÆ“n‚µ
	this->move(_stage, dx, dy);

	p->raw_x += dx;
	p->raw_y += dy;
}


void BossChild::checkIsAlive(const Stage* _stage)
{
	mIsAlive &= (this->hpController.getHP() > 0);
	mIsAlive &= (this->p->raw_y % MyData::MAP_HEIGHT_RATE() < (this->p->raw_y + 10000) % MyData::MAP_HEIGHT_RATE());
	mIsAlive &= (this->p->raw_y % MyData::MAP_HEIGHT_RATE() > (this->p->raw_y - 10000) % MyData::MAP_HEIGHT_RATE());
}

void BossChild::processDamage()
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