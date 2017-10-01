#include "Stage22.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage22::Stage22() :
StageChild(2, 2) //エリアの数: よこ，たて
{
	initialize();
}

Stage22::~Stage22()
{

}

void Stage22::initialize()
{
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(22, 0, MapPos::POS_LEFT_UP));
	this->maps.push_back(new Map(22, 1, MapPos::POS_LEFT_FREE));
	this->maps.push_back(new Map(22, 2, MapPos::POS_UP_FREE));
	this->maps.push_back(new Map(22, 3, MapPos::POS_SINGLE));

	flag = new ClearFlag(Vector2(2608, 1040));
	maps[1]->addGimmick(flag);

	//for Debug
	/*
	maps[0]->addEnemy(AllEnemies::BOSS_REISEN, 640, 1392);
	maps[0]->addEnemy(AllEnemies::ENE_AIRMZ, 540, 1392);
	maps[0]->addEnemy(AllEnemies::ENE_BROTH, 540, 1488);
	*/
	//maps[0]->addEnemy(AllEnemies::BOSS_JUNKO, 540, 1360);
}


void Stage22::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(22);
}

void Stage22::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage22::isClear() const
{
	return false;
}


}
}
}


