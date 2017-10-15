#include "Stage13.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include "..\Gimmick\DynamicGimmickChild.h"
#include "..\Player\PlayerChild.h"
#include "..\Gimmick\Door.h"
#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage13::Stage13() :
StageChild(4, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage13::~Stage13()
{
	
}

void Stage13::initialize()
{

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(13, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(13, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(13, 2, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(13, 3, MapPos::POS_LEFT_FREE));

	flag = new ClearFlag(Vector2(3056, 1264));
	maps[0]->addGimmick(flag);

	Door* d = new Door(new Vector2(8 * 32 + 16, 27 * 32 + 16), new Vector2(78 * 32 + 16, 32 * 32 + 16));
	maps[3]->addGimmick(d);

	SwitchWithBlock* s = new SwitchWithBlock(76 * 32 + 16, 37 * 32 + 16, 390);
	for (int i = 0; i < 4; i++)s->push_block(new Block(76 * 32 + 16, (40 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[1]->addSwitchWithBlock(s);

	maps[3]->addEnemy(BOSS_REISEN, 88 * 32, 48 * 32);

	startX = 208, startY = 1440;

	converseFlag0 = true;
	converseFlag1 = true;
}


void Stage13::update(GameMain* gameMain, PlayerChild* _player)
{
	
	if(now_stage_num == 3 && converseFlag0 &&_player->getVector2()->y()==1536)
	{
		gameMain->startConverse(130);
		converseFlag0 = false;
	}

	
	standardUpdate(_player);

}

void Stage13::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
	if (!converseFlag1)DrawBox(0, 0, 640, 480, BLACK, TRUE);
}

bool Stage13::isClear() const
{
	return !flag->isActive;
}


}
}
}


