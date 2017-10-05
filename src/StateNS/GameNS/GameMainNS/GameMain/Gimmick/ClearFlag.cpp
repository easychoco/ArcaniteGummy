#include "ClearFlag.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

bool ClearFlag::imgLoad = false;
int ClearFlag::image;

ClearFlag::ClearFlag(Vector2 _pos) : 
GimmickChild(_pos)
{
	initialize();
	
}

ClearFlag::~ClearFlag()
{
	//DeleteGraphはしない
}

void ClearFlag::initialize()
{
	loadImage();
	mImage = image;
}

void ClearFlag::update()
{

}

void ClearFlag::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

void ClearFlag::apply(Character* _character)
{
	this->isActive = false;
}

bool ClearFlag::isOverlap(int _sub_x, int _sub_y) const
{
	return
		this->pos.x() / CHIP_WIDTH  == _sub_x &&
		this->pos.y() / CHIP_HEIGHT == _sub_y;
}

bool ClearFlag::onActiveArea(const Vector2* _player) const
{
	return
		abs(this->pos.x() - _player->x()) <= CHIP_WIDTH / 2 &&
		abs(this->pos.y() - _player->y()) <= MyData::CHIP_HEIGHT;}

StageChild::ChipType ClearFlag::getChipType() const
{
	return StageChild::ChipType::TYPE_BACK;
}

//==============================================
//内部プライベート関数
//==============================================
void ClearFlag::loadImage()
{
	if (!imgLoad)
	{
		image = LoadGraph("Data/Image/ClearFlag.png");
		assert(image != -1 && "クリア画像読み込みエラー！");
	}
	imgLoad = true;
}


}
}
}