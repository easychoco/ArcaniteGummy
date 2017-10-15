#include "FallFloor.h"

#include "..\Character.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

bool FallFloor::imgLoad = false;
int FallFloor::image;

FallFloor::FallFloor(int _x, int _y, bool _falldown) : 
DynamicGimmickChild(_x, _y, 1.0)
{
	this->width  = 96;
	this->height = 32;

	this->falldown = _falldown;
	this->nowFall = false;
	this->sy = _y*vectorRate;
	initialize();
}

FallFloor::~FallFloor()
{
	//DeleteGraphはしない
}


void FallFloor::initialize()
{
	this->mTime = 0;
	this->mTime2 = 0;
	loadImage();
	mImage = image;
}

void FallFloor::update(const StageChild* _stage)
{
	if(nowFall)mTime++;
	if (sy != this->p->raw_y)mTime2++;

	if (mTime2 == 150 || mTime>40)
	{
		nowFall = false;
		mTime2 = 0;
		mTime = 0;
		this->p->raw_y = sy;
	}



	move(_stage);
	standardMove(_stage);

}

void FallFloor::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(p->raw_x - _camera->raw_x) > 480000 || abs(p->raw_y - _camera->raw_y) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	DrawRotaGraph(draw_x, draw_y, 1.0, Pi*!falldown, mImage, true, mDirection);
}

void FallFloor::apply(Character* _character)
{
	_character->moveCharacter((float)dx / vectorRate, (float)dy / vectorRate);
	nowFall = true;
	_character->setJumpCount(0);

}

void FallFloor::hittedAction()
{
	/*do nothing*/
}

void FallFloor::burnedAction()
{
	/*do nothing*/
}

bool FallFloor::isOverlap(const Vector2* _player) const
{
	return standardOverLap(_player);

	/*
	int tmp_w = this->width  * vectorRate / 2;
	int tmp_h = this->height * vectorRate / 2;

	return
		this->p->raw_x - tmp_w < _player->raw_x &&
		this->p->raw_x + tmp_w > _player->raw_x &&
		this->p->raw_y - tmp_h < _player->raw_y &&
		this->p->raw_y + tmp_h > _player->raw_y;
	*/

	/* Collisionの当たり判定
	return
		this->p->raw_x			      < other->p->raw_x + other->width  &&
		this->p->raw_x + this->width  > other->p->raw_x					&&
		this->p->raw_y			      < other->p->raw_y + other->height &&
		this->p->raw_y + this->height > other->p->raw_y;
	*/
}

bool FallFloor::onActiveArea(const Vector2* _player) const
{
	return
		abs(this->p->x() - _player->x()) <= MyData::CHIP_WIDTH &&
		(this->p->y() - _player->y()) / MyData::CHIP_HEIGHT == 1;
}

//==============================================
//内部プライベート関数
//==============================================
void FallFloor::loadImage()
{
	if (!imgLoad)
	{
		image = LoadGraph("Data/Image/FallFloor.png");
		assert(mImage != -1 && "FallFloor画像読み込みエラー!");
	}
	imgLoad = true;
}

void FallFloor::move(const StageChild* _stage)
{
	int tmp_dy = falldown ? getBottomDiffer(_stage, mTime*mTime, dx < 0) : getTopDiffer(_stage, -mTime*mTime, dx < 0);
	if (tmp_dy == 0)
	{
		mTime = 0;
		nowFall = false;
	}


	dy = (int)(tmp_dy / 100.0f * vectorRate);


}


}
}
}