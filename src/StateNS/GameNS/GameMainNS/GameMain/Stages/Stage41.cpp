#include "stage41.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

stage41::stage41() :
StageChild(2, 1) //エリアの数: よこ，たて
{
	initialize();
}

stage41::~stage41()
{

}

void stage41::initialize()
{
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(41, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(41, 1, MapPos::POS_LEFT_FREE));

	flag = new ClearFlag(Vector2(3056, 240));
	maps[1]->addGimmick(flag);

	startX = 144, startY = 1536;

}


void stage41::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(12);
}

void stage41::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool stage41::isClear() const
{
	return false;
}


}
}
}


