#include "..\Player\PlayerChild.h"
#include "Switch.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Switch::Switch(){
	initialize();
}

Switch::~Switch()
{

}

void Switch::initialize()
{
	this->pos = Vector2(0, 0);
	w = MyData::CHIP_WIDTH;
	h = MyData::CHIP_HEIGHT;
}

void Switch::update(PlayerChild* _player)
{


}

void Switch::draw() const
{
	DrawFormatString(0, 20, MyData::WHITE, "Switch");
}

bool Switch::isHit(const Vector2& _other) const
{
	return _other.x() / MyData::CHIP_WIDTH  == this->pos.x()
		&& _other.y() / MyData::CHIP_HEIGHT == this->pos.y();
}

Stage::ChipType Switch::getChipType() const
{
	//スイッチは透過
	return Stage::ChipType::TYPE_BACK;
}



//==============================================
//内部プライベート関数
//==============================================

//そんなものはない



}
}
}