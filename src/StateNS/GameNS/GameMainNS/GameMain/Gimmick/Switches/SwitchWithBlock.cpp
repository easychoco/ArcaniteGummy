#include "SwitchWithBlock.h"

#include "..\..\Character.h"
#include "..\Block.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

SwitchWithBlock::SwitchWithBlock(int x, int y) : SwitchWithBlock(x, y, 1 << 29, false)
{

}

SwitchWithBlock::SwitchWithBlock(int x, int y, int f) : 
SwitchWithBlock(x, y, ((f < 2) ? 1 << 29 : f), f == 1)
{

}


SwitchWithBlock::SwitchWithBlock(int _x, int _y, int _limitTime, bool _notChangeable) : 
DynamicGimmickChild(_x, _y, 1.0),
limitTime(_limitTime),
notChangeable(_notChangeable)
{
	initialize();
}

SwitchWithBlock::~SwitchWithBlock()
{
	for (auto& block : blocks_on)
	{
		SAFE_DELETE(block);
	}
	blocks_on.clear();
	blocks_on.shrink_to_fit();

	for (auto& block : blocks_off)
	{
		SAFE_DELETE(block);
	}
	blocks_off.clear();
	blocks_off.shrink_to_fit();

	DeleteGraph(mImage);
}

void SwitchWithBlock::initialize()
{
	loadImage();

	isActive = true;
	this->isPushed = false;
	this->preOnActiveArea = false;
	this->mTime = 0;
}

void SwitchWithBlock::update(const StageChild* _stage)
{
	++mTime;
	if (mTime > limitTime)
	{
		isPushed = false;
		mTime = 0;
	}
	preOnActiveArea = tmpOnActiveArea;
	tmpOnActiveArea = false;
}

void SwitchWithBlock::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(p->raw_x - _camera->raw_x) > 350000 || abs(p->raw_y - _camera->raw_y) > 270000)return;

	int draw_x = 320 + (p->raw_x - _camera->raw_x) / MyData::vectorRate;
	int draw_y = 240 + (p->raw_y - _camera->raw_y) / MyData::vectorRate;

	//描画
	if(!isPushed)DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true);
	else DrawCircle(draw_x, draw_y, 5, GREEN);
}

void SwitchWithBlock::apply(Character* _character)
{
	if (notChangeable)
	{
		isPushed = true;
		return;
	}
	if(!preOnActiveArea && mTime > 5)isPushed = !isPushed;
	mTime = 0;
}

void SwitchWithBlock::hittedAction()
{
	if (!preOnActiveArea && mTime > 5)isPushed = !isPushed;
	mTime = 0;
}

void SwitchWithBlock::burnedAction()
{

}

bool SwitchWithBlock::isOverlap(const Vector2* _player) const
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

bool SwitchWithBlock::onActiveArea(const Vector2* _player) const
{
	bool tmp = 
		abs(this->p->x() - _player->x()) <= MyData::CHIP_WIDTH  / 2 &&
		abs(this->p->y() - _player->y()) <= MyData::CHIP_HEIGHT / 2;

	this->tmpOnActiveArea |= tmp;

	return tmp;
}

StageChild::ChipType SwitchWithBlock::getChipType() const
{
	return StageChild::ChipType::TYPE_BACK;
}

//==============================================
//内部プライベート関数
//==============================================
void SwitchWithBlock::loadImage()
{
	//TODO 画像差し替え
	mImage = LoadGraph("Data/Image/switch.png");
	assert(mImage != -1 && "スイッチ画像読み込みエラー！");
}


}
}
}