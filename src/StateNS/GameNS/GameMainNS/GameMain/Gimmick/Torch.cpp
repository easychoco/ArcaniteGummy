#include "Torch.h"

#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Torch::Torch(int _x, int _y) : 
DynamicGimmickChild(_x, _y, 1.0)
{
	initialize();
}

Torch::~Torch()
{
	DeleteGraph(mImage);
}

void Torch::initialize()
{
	loadImage();

	isActive = true;
	this->isBurned = false;
	this->mTime = 0;
}

void Torch::update(const StageChild* _stage)
{
	++mTime;
	if (mTime > 600)isBurned = false;
}

void Torch::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(p->pos_x() - _camera->pos_x()) > 350000 || abs(p->pos_y() - _camera->pos_y()) > 270000)return;

	int draw_x = 320 + (p->pos_x() - _camera->pos_x()) / MyData::vectorRate;
	int draw_y = 240 + (p->pos_y() - _camera->pos_y()) / MyData::vectorRate;

	//描画
	//if(!isPushed)DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true);
	//else DrawCircle(draw_x, draw_y, 5, GREEN);
}

void Torch::apply(Character* _character)
{
	
}

void Torch::hittedAction()
{

}

void Torch::burnedAction()
{
	this->isBurned = true;
	mTime = 0;
}

bool Torch::isOverlap(const Vector2* _player) const
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

bool Torch::onActiveArea(const Vector2* _player) const
{
	return false;
}

StageChild::ChipType Torch::getChipType() const
{
	return StageChild::ChipType::TYPE_BACK;
}

//==============================================
//内部プライベート関数
//==============================================
void Torch::loadImage()
{
	//TODO 画像差し替え
	mImage = LoadGraph("Data/Image/switch.png");
	assert(mImage != -1 && "スイッチ画像読み込みエラー！");
}


}
}
}