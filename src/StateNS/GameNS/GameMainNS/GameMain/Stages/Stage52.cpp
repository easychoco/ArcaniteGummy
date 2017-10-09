#include "Stage52.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage52::Stage52() :
StageChild(2, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage52::~Stage52()
{

}

void Stage52::initialize()
{

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;
	this->changeableCharacter |= CHARA_NUE;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(42, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(42, 1, MapPos::POS_LEFT_FREE));

	flag = new ClearFlag(Vector2(2384, 1360));
	maps[1]->addGimmick(flag);

	SwitchWithBlock* s = new SwitchWithBlock(41 * 32 + 16, 36 * 32 + 16);
	for (int i = 0; i < 2; i++)s->push_block(new Block((29 + i) * 32 + 16, 37 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	for (int i = 0; i < 2; i++)s->push_block(new Block((31 + i) * 32 + 16, 37 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	for (int i = 0; i < 2; i++)s->push_block(new Block((33 + i) * 32 + 16, 37 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	for (int i = 0; i < 2; i++)s->push_block(new Block((35 + i) * 32 + 16, 37 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	for (int i = 0; i < 2; i++)s->push_block(new Block((37 + i) * 32 + 16, 37 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[0]->addSwitchWithBlock(s);

	SwitchWithBlock* s2 = new SwitchWithBlock(97 * 32 + 16, 37 * 32 + 16);
	for (int i = 0; i < 4; i++)s->push_block(new Block((90 + i) * 32 + 16, 35 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[0]->addSwitchWithBlock(s2);

	SwitchWithBlock* s3 = new SwitchWithBlock(82 * 32 + 16, 27 * 32 + 16);
	for (int i = 0; i < 3; i++)s3->push_block(new Block((85 + i) * 32 + 16, 25 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[0]->addSwitchWithBlock(s3);

	SwitchWithBlock* s4 = new SwitchWithBlock(97 * 32 + 16, 17 * 32 + 16);
	for (int i = 0; i < 3; i++)s4->push_block(new Block((89 + i) * 32 + 16, 18 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	for (int i = 0; i < 3; i++)s4->push_block(new Block((92 + i) * 32 + 16, 14 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[0]->addSwitchWithBlock(s4);

	SwitchWithBlock* s5 = new SwitchWithBlock(78 * 32 + 16, 11 * 32 + 16);
	for (int i = 0; i < 3; i++)s5->push_block(new Block((92 + i) * 32 + 16, 8 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	for (int i = 0; i < 3; i++)s5->push_block(new Block((82 + i) * 32 + 16, 8 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[0]->addSwitchWithBlock(s5);


	SwitchWithBlock* s6 = new SwitchWithBlock(98 * 32 + 16, 32 * 32 + 16);
	for (int i = 0; i < 3; i++)s6->push_block(new Block(83 * 32 + 16, (37 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[1]->addSwitchWithBlock(s6);


	maps[0]->addSwitchWithBlock(s4);


	startX = 144, startY = 1536;
	//for Debug
	/*
	maps[0]->addEnemy(AllEnemies::BOSS_REISEN, 640, 1392);
	maps[0]->addEnemy(AllEnemies::ENE_AIRMZ, 540, 1392);
	maps[0]->addEnemy(AllEnemies::ENE_BROTH, 540, 1488);
	*/
	//maps[0]->addEnemy(AllEnemies::BOSS_JUNKO, 540, 1360);
}


void Stage52::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(12);
}

void Stage52::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage52::isClear() const
{
	return !flag->isActive;
}


}
}
}


