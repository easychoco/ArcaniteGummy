#include "Stage21.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage21::Stage21() :
StageChild(3, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage21::~Stage21()
{

}

void Stage21::initialize()
{
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(21, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(21, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(21, 2, MapPos::POS_LEFT_FREE));

}


void Stage21::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(21);
}

void Stage21::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage21::isClear() const
{
	return false;
}


}
}
}


