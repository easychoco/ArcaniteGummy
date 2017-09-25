#include "Stage11.h"
#include "Map.h"
#include "..\..\GameMain.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage11::Stage11() :
StageChild(2, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage11::~Stage11()
{

}

void Stage11::initialize()
{
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(11, 0, MapPos::POS_LEFT_DOWN));
	this->maps.push_back(new Map(11, 1, MapPos::POS_RIGHT_DOWN));

}


void Stage11::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(12);
}

void Stage11::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage11::isClear() const
{
	return false;
}


}
}
}


