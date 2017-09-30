#include "Stage32.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage32::Stage32() :
StageChild(2, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage32::~Stage32()
{

}

void Stage32::initialize()
{
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(32, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(32, 1, MapPos::POS_LEFT_FREE));

	//for Debug
	/*
	maps[0]->addEnemy(AllEnemies::BOSS_REISEN, 640, 1392);
	maps[0]->addEnemy(AllEnemies::ENE_AIRMZ, 540, 1392);
	maps[0]->addEnemy(AllEnemies::ENE_BROTH, 540, 1488);
	*/
	//maps[0]->addEnemy(AllEnemies::BOSS_JUNKO, 540, 1360);
}


void Stage32::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(12);
}

void Stage32::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage32::isClear() const
{
	return false;
}


}
}
}


