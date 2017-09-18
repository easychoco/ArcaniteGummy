#include "SwitchWithBlock.h"

#include "..\..\Character.h"
#include "..\Block.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


SwitchWithBlock::SwitchWithBlock(int _x, int _y) : 
DynamicGimmickChild(_x, _y, 1.0)
{
	initialize();
}

SwitchWithBlock::~SwitchWithBlock()
{
	for (auto& block : blocks)
	{
		SAFE_DELETE(block);
	}
	blocks.clear();
	blocks.shrink_to_fit();
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
	preOnActiveArea = tmpOnActiveArea;
	tmpOnActiveArea = false;
}

void SwitchWithBlock::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(p->pos_x() - _camera->pos_x()) > 350000 || abs(p->pos_y() - _camera->pos_y()) > 270000)return;

	int draw_x = 320 + (p->pos_x() - _camera->pos_x()) / MyData::vectorRate;
	int draw_y = 240 + (p->pos_y() - _camera->pos_y()) / MyData::vectorRate;

	//描画
	if(!isPushed)DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true);
	else DrawCircle(draw_x, draw_y, 5, GREEN);
}

void SwitchWithBlock::apply(Character* _character)
{
	if(!preOnActiveArea)isPushed = !isPushed;
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
	bool gomi = 
		abs(this->p->x() - _player->x()) <= MyData::CHIP_WIDTH  / 2 &&
		abs(this->p->y() - _player->y()) <= MyData::CHIP_HEIGHT / 2;

	this->tmpOnActiveArea |= gomi;

	return gomi;
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