#include "OrderEmergeFloor.h"

#include "..\Character.h"


//for Debug
#include "..\Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

bool OrderEmergeFloor::imgLoad = false;
int OrderEmergeFloor::image;

OrderEmergeFloor::OrderEmergeFloor(int _x, int _y, double _scale, int _order) :
DynamicGimmickChild(_x, _y, 1.0)
{
	this->width = 96;
	this->height = 32;
	this->order = _order;
	this->isEmerge = false;
	initialize();
}

OrderEmergeFloor::~OrderEmergeFloor()
{
	//DeleteGraphはしない
}

void OrderEmergeFloor::initialize()
{
	loadImage();

	mImage = image;

	this->mTime = 0;
}

void OrderEmergeFloor::update(const StageChild* _stage)
{
	mTime++;
	mTime %= 240;

	if (mTime >= order * 30)isEmerge = true;
	else isEmerge = false;

	//if (!isEmerge)return;
	standardMove(_stage);
	//this->dy = getBottomDiffer(_stage, 4000);
	//this->p->raw_y += this->dy;
}

void OrderEmergeFloor::draw(const Vector2* _camera) const
{
	DrawFormatString(100, 100, BLACK, "%d,%d", this->width, this->height);
	if (!isEmerge)return;

	standardDraw(_camera, scale, mImage, mDirection);
}

void OrderEmergeFloor::apply(Character* _character)
{

	//_character->moveCharacter(0.0f, (float)dy);
}

void OrderEmergeFloor::hittedAction()
{
//	if(isBreakable)this->isActive = false;
}

void OrderEmergeFloor::burnedAction()
{
	//TODO -> アニメーションをつける

	//燃やされると消える
	//this->isActive = false;
}

bool OrderEmergeFloor::isOverlap(const Vector2* _player) const
{
	if (!isEmerge)return false;
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

bool OrderEmergeFloor::onActiveArea(const Vector2* _player) const
{
	return
		abs(this->p->x() - _player->x()) <= MyData::CHIP_WIDTH &&
		(this->p->y() - _player->y()) / MyData::CHIP_HEIGHT == 1;
}


//==============================================
//内部プライベート関数
//==============================================
void OrderEmergeFloor::loadImage()
{
	if (!imgLoad)
	{
		this->image = LoadGraph("Data/Image/OrderEmergeFloor.png");
		assert(image != -1 && "OrderEmergeFloor画像読み込みエラー!");
	}
	imgLoad = true;
}


}
}
}