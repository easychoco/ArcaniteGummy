#include "Stage52.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage52::Stage52() :
StageChild(3, 2) //エリアの数: よこ，たて
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
	this->maps.push_back(new Map(52, 0, MapPos::POS_DOWN_FREE));
	this->maps.push_back(new Map(52, 1, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(52, 2, MapPos::POS_RIGHT_UP));
	this->maps.push_back(new Map(52, 3, MapPos::POS_LEFT_DOWN));
	this->maps.push_back(new Map(52, 4, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(52, 5, MapPos::POS_RIGHT_DOWN));


	flag = new ClearFlag(Vector2(97 * 32 + 16, 6 * 32 + 16));
	maps[0]->addGimmick(flag);
	now_stage_num = 1;
	startX = 144, startY = 1536;

	SwitchWithBlock* s = new SwitchWithBlock(91 * 32 + 16, 12 * 32 + 16, 1);
	for (int i = 0; i < 6; i++)s->push_block(new Block((92 + i) * 32 + 16, 13 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[2]->addSwitchWithBlock(s);
	SwitchWithBlock* s1 = new SwitchWithBlock(98 * 32 + 16, 12 * 32 + 16, 1);
	for (int i = 0; i < 6; i++)s1->push_block(new Block((92 + i) * 32 + 16, 13 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[2]->addSwitchWithBlock(s1);

	SwitchWithBlock* s2 = new SwitchWithBlock(66 * 32 + 16, 20 * 32 + 16, 99);
	for (int i = 0; i < 3; i++)s2->push_block(new Block((63 + i) * 32 + 16, 20 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[3]->addSwitchWithBlock(s2);
	SwitchWithBlock* s3 = new SwitchWithBlock(58 * 32 + 16, 23 * 32 + 16, 99);
	for (int i = 0; i < 3; i++)s3->push_block(new Block((59 + i) * 32 + 16, 23 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[3]->addSwitchWithBlock(s3);
	SwitchWithBlock* s4 = new SwitchWithBlock(66 * 32 + 16, 26 * 32 + 16, 99);
	for (int i = 0; i < 3; i++)s4->push_block(new Block((63 + i) * 32 + 16, 26 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[3]->addSwitchWithBlock(s4);
	SwitchWithBlock* s5 = new SwitchWithBlock(58 * 32 + 16, 29 * 32 + 16, 99);
	for (int i = 0; i < 3; i++)s5->push_block(new Block((59 + i) * 32 + 16, 29 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[3]->addSwitchWithBlock(s5);

	SwitchWithBlock* s6 = new SwitchWithBlock(80 * 32 + 16, 28 * 32 + 16, 99);
	for (int i = 0; i < 4; i++)s6->push_block(new Block(77 * 32 + 16, (28 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[3]->addSwitchWithBlock(s6);
	SwitchWithBlock* s7 = new SwitchWithBlock(80 * 32 + 16, 31 * 32 + 16, 99);
	for (int i = 0; i < 4; i++)s7->push_block(new Block(77 * 32 + 16, (28 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[3]->addSwitchWithBlock(s7);
	SwitchWithBlock* s8 = new SwitchWithBlock(92 * 32 + 16, 31 * 32 + 16, 99);
	for (int i = 0; i < 4; i++)s8->push_block(new Block(87 * 32 + 16, (28 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[3]->addSwitchWithBlock(s8);
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


