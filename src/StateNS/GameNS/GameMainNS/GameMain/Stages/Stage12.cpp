#include "Stage12.h"
#include "Map.h"
#include "..\..\GameMain.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage12::Stage12() :
StageChild(2, 2) //エリアの数: よこ，たて
{
	initialize();
}

Stage12::~Stage12()
{

}

void Stage12::initialize()
{
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(12, 0, MapPos::POS_LEFT_UP));
	this->maps.push_back(new Map(12, 1, MapPos::POS_RIGHT_UP));
	this->maps.push_back(new Map(12, 2, MapPos::POS_LEFT_DOWN));
	this->maps.push_back(new Map(12, 3, MapPos::POS_RIGHT_DOWN));

	//maps[0]->addEnemy(AllEnemies::BOSS_REISEN, 640, 1392);
	//maps[0]->addEnemy(AllEnemies::ENE_AIRMZ, 540, 1392);
	//maps[0]->addEnemy(AllEnemies::ENE_BROTH, 540, 1488);
	//maps[0]->addEnemy(AllEnemies::ENE_TERESA, 540, 1360);

}


void Stage12::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(12);
}

void Stage12::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage12::isClear() const
{
	return false;
}


}
}
}


