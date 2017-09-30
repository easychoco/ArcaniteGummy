#include "stage42.h"
#include "Map.h"
#include "..\..\GameMain.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

stage42::stage42() :
StageChild(2, 1) //エリアの数: よこ，たて
{
	initialize();
}

stage42::~stage42()
{

}

void stage42::initialize()
{
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(42, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(42, 1, MapPos::POS_LEFT_FREE));

	//for Debug
	/*
	maps[0]->addEnemy(AllEnemies::BOSS_REISEN, 640, 1392);
	maps[0]->addEnemy(AllEnemies::ENE_AIRMZ, 540, 1392);
	maps[0]->addEnemy(AllEnemies::ENE_BROTH, 540, 1488);
	*/
	//maps[0]->addEnemy(AllEnemies::BOSS_JUNKO, 540, 1360);
}


void stage42::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(12);
}

void stage42::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool stage42::isClear() const
{
	return false;
}


}
}
}


