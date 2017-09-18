#include "Stage12.h"
#include "Map.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage12::Stage12() :
StageChild(2, 2)
{
	initialize();
}

Stage12::~Stage12()
{

}

void Stage12::update(PlayerChild* _player)
{
	standardUpdate(_player);
}

void Stage12::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage12::isClear() const
{
	return false;
}


void Stage12::initialize()
{
	//256*480
	int tmp = LoadDivGraph("Data/Image/block0.png", 256, 8, 15, 32, 32, mapChip);
	assert(tmp != -1 && "マップチップ読み込みエラー");

	this->maps.push_back(new Map(12, 0, MapPos::POS_LEFT_UP));
	this->maps.push_back(new Map(12, 1, MapPos::POS_RIGHT_UP));
	this->maps.push_back(new Map(12, 2, MapPos::POS_LEFT_DOWN));
	this->maps.push_back(new Map(12, 3, MapPos::POS_RIGHT_DOWN));
}

}
}
}


