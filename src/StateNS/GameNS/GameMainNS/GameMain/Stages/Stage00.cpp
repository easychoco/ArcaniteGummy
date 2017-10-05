#include "Stage00.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\AllGimmicks.h"

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

	maps[0]->addEnemy(AllEnemies::ENE_USA, 1540, 1552);

	/*
	maps[0]->addDynamicGimmick(new OrderEmergeFloor(80, 1520, 1.0f, 1));
	maps[0]->addDynamicGimmick(new FallFloor(176, 1520, false));

	SwitchWithBlock* s = new SwitchWithBlock(208, 1488);
	s->push_block(new Block(208, 1296, 1.0), true);
	s->push_block(new Block(256, 1312, 2.0), false);
	maps[0]->addSwitchWithBlock(s);
	SwitchWithBlock* s2 = new SwitchWithBlock(272, 1488);
	s2->push_block(new Block(272, 1296, 1.0), true);
	s2->push_block(new Block(288, 1312, 2.0), false);
	maps[0]->addSwitchWithBlock(s2);

	MovingFloor* mv_tmp = new MovingFloor(304, 1488, 400, 1200, 2, 0);
	maps[0]->addDynamicGimmick(mv_tmp);

	Dossunn* d_tmp = new Dossunn(272, 1488, 1.0);
	maps[0]->addDynamicGimmick(d_tmp);
	*/

	maps[0]->addDynamicGimmick(new Block(240, 1520, 1.0));
	maps[0]->addDynamicGimmick(new Block(272, 1520, 1.0));
	maps[0]->addDynamicGimmick(new Block(304, 1520, 1.0));
	maps[0]->addDynamicGimmick(new Block(336, 1520, 1.0));
	
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


