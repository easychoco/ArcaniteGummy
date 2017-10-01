#include "Stage00.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>
/////////////////////////////////////////////デバッグ用ステージ/////////////////////
namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage00::Stage00() :
StageChild(2, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage00::~Stage00()
{

}

void Stage00::initialize()
{
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(0, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(0, 1, MapPos::POS_LEFT_FREE));

	//this->maps[0]->addEnemy(BOSS_JUNKO, 540, 1488);

	flag = new ClearFlag(Vector2(3056, 1264));
	maps[0]->addGimmick(flag);
	
	startX = 144, startY = 1536;
}


void Stage00::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(11);
}

void Stage00::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage00::isClear() const
{
	return !flag->isActive;
}


}
}
}


