#include "Stage52.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"
#include "..\Player\PlayerChild.h"
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
	sound->deleteSound("bgm5");
}

void Stage52::initialize()
{
	sound->setSound("Data/Sound/stage5.wav", "bgm5");
	sound->playSound("bgm5", LOOP, false);

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

	switchset();
	time = 0;
	findRestartPoint();
}

void Stage52::switchset() 
{
	SwitchWithBlock* ss01 = new SwitchWithBlock(63 * 32 + 16, 10 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)ss01->push_block(new Block(86 * 32 + 16, (8 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(ss01);
	SwitchWithBlock* ss02 = new SwitchWithBlock(69 * 32 + 16, 10 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)ss02->push_block(new Block(86 * 32 + 16, (8 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(ss02);
	SwitchWithBlock* ss03 = new SwitchWithBlock(75 * 32 + 16, 10 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)ss03->push_block(new Block(86 * 32 + 16, (8 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(ss03);
	SwitchWithBlock* ss04 = new SwitchWithBlock(81 * 32 + 16, 10 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)ss04->push_block(new Block(86 * 32 + 16, (8 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(ss04);
	SwitchWithBlock* ss05 = new SwitchWithBlock(63 * 32 + 16, 16 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)ss05->push_block(new Block(86 * 32 + 16, (8 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(ss05);
	SwitchWithBlock* ss06 = new SwitchWithBlock(69 * 32 + 16, 16 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)ss06->push_block(new Block(86 * 32 + 16, (8 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(ss06);
	SwitchWithBlock* ss07 = new SwitchWithBlock(75 * 32 + 16, 16 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)ss07->push_block(new Block(86 * 32 + 16, (8 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(ss07);
	SwitchWithBlock* ss08 = new SwitchWithBlock(81 * 32 + 16, 16 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)ss08->push_block(new Block(86 * 32 + 16, (8 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(ss08);
	SwitchWithBlock* ss09 = new SwitchWithBlock(63 * 32 + 16, 22 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)ss09->push_block(new Block(86 * 32 + 16, (8 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(ss09);
	SwitchWithBlock* ss10 = new SwitchWithBlock(69 * 32 + 16, 22 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)ss10->push_block(new Block(86 * 32 + 16, (8 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(ss10);
	SwitchWithBlock* ss11 = new SwitchWithBlock(75 * 32 + 16, 22 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)ss11->push_block(new Block(86 * 32 + 16, (8 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(ss11);
	SwitchWithBlock* ss12 = new SwitchWithBlock(81 * 32 + 16, 22 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)ss12->push_block(new Block(86 * 32 + 16, (8 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(ss12);





	SwitchWithBlock* s = new SwitchWithBlock(91 * 32 + 16, 12 * 32 + 16, 30);
	for (int i = 0; i < 6; i++)s->push_block(new Block((92 + i) * 32 + 16, 13 * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(s);
	SwitchWithBlock* s1 = new SwitchWithBlock(98 * 32 + 16, 12 * 32 + 16, 30);
	for (int i = 0; i < 6; i++)s1->push_block(new Block((92 + i) * 32 + 16, 13 * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(s1);

	SwitchWithBlock* sf1 = new SwitchWithBlock(86 * 32 + 16, 7 * 32 + 16, 1);
	for (int i = 0; i < 5; i++)sf1->push_block(new Block(0 * 32 + 16, (41 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[5]->addSwitchWithBlock(sf1);
	SwitchWithBlock* sf2 = new SwitchWithBlock(86 * 32 + 16, 44 * 32 + 16, 1);
	for (int i = 0; i < 5; i++)sf2->push_block(new Block(0 * 32 + 16, (41 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[5]->addSwitchWithBlock(sf2);
	SwitchWithBlock* sf3 = new SwitchWithBlock(3 * 32 + 16, 7 * 32 + 16, 1);
	for (int i = 0; i < 5; i++)sf3->push_block(new Block(0 * 32 + 16, (41 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[5]->addSwitchWithBlock(sf3);




	SwitchWithBlock* s2 = new SwitchWithBlock(66 * 32 + 16, 20 * 32 + 16, 90);
	for (int i = 0; i < 3; i++)s2->push_block(new Block((63 + i) * 32 + 16, 20 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[3]->addSwitchWithBlock(s2);
	SwitchWithBlock* s3 = new SwitchWithBlock(58 * 32 + 16, 23 * 32 + 16, 90);
	for (int i = 0; i < 3; i++)s3->push_block(new Block((59 + i) * 32 + 16, 23 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[3]->addSwitchWithBlock(s3);
	SwitchWithBlock* s4 = new SwitchWithBlock(66 * 32 + 16, 26 * 32 + 16, 90);
	for (int i = 0; i < 3; i++)s4->push_block(new Block((63 + i) * 32 + 16, 26 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[3]->addSwitchWithBlock(s4);
	SwitchWithBlock* s5 = new SwitchWithBlock(58 * 32 + 16, 29 * 32 + 16, 90);
	for (int i = 0; i < 3; i++)s5->push_block(new Block((59 + i) * 32 + 16, 29 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[3]->addSwitchWithBlock(s5);

	SwitchWithBlock* s6 = new SwitchWithBlock(80 * 32 + 16, 28 * 32 + 16, 90);
	for (int i = 0; i < 4; i++)s6->push_block(new Block(77 * 32 + 16, (28 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[3]->addSwitchWithBlock(s6);
	SwitchWithBlock* s7 = new SwitchWithBlock(80 * 32 + 16, 31 * 32 + 16, 90);
	for (int i = 0; i < 4; i++)s7->push_block(new Block(77 * 32 + 16, (28 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[3]->addSwitchWithBlock(s7);
	SwitchWithBlock* s8 = new SwitchWithBlock(92 * 32 + 16, 31 * 32 + 16, 90);
	for (int i = 0; i < 4; i++)s8->push_block(new Block(87 * 32 + 16, (28 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[3]->addSwitchWithBlock(s8);

	SwitchWithBlock* s9 = new SwitchWithBlock(95 * 32 + 16, 48 * 32 + 16, 1200);
	for (int i = 0; i < 5; i++)s9->push_block(new Block(89 * 32 + 16, (1 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[0]->addSwitchWithBlock(s9);

}

void Stage52::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);
	if (now_stage_num != 0)return;
	time++;
	if (time % 900 == 0)maps[0]->addEnemy(ENE_TERESA, _player->getVector2(), 99 * 32, 27 * 32);
	if (time % 900 == 450)maps[0]->addEnemy(ENE_TERESA, _player->getVector2(), 58 * 32, 27 * 32);

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


