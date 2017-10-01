#include "Stage31.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage31::Stage31() :
StageChild(2, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage31::~Stage31()
{

}

void Stage31::initialize()
{
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(31, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(31, 1, MapPos::POS_LEFT_FREE));

	flag = new ClearFlag(Vector2(1936, 1552));
	maps[1]->addGimmick(flag);

	startX = 144, startY = 1536;

}


void Stage31::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(31);
}

void Stage31::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage31::isClear() const
{
	return false;
}


}
}
}


