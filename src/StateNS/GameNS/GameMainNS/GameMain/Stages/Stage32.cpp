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

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(32, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(32, 1, MapPos::POS_LEFT_FREE));


	flag = new ClearFlag(Vector2(592, 1552));
	maps[1]->addGimmick(flag);

	startX = 3088, startY = 1536;

	SwitchWithBlock* s = new SwitchWithBlock(3 * 32 + 16, 48 * 32 + 16, 300);
	for (int i = 0; i < 4; i++)s->push_block(new Block((5 + i) * 32 + 16, 44 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[0]->addSwitchWithBlock(s);


	SwitchWithBlock* s2 = new SwitchWithBlock(56 * 32 + 16, 39 * 32 + 16);
	for (int i = 0; i < 3; i++)s2->push_block(new Block((42 + i) * 32 + 16, 40 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	for (int i = 0; i < 3; i++)s2->push_block(new Block((45 + i) * 32 + 16, 40 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	for (int i = 0; i < 3; i++)s2->push_block(new Block((48 + i) * 32 + 16, 40 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	for (int i = 0; i < 4; i++)s2->push_block(new Block(44 * 32 + 16, (36 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	for (int i = 0; i < 4; i++)s2->push_block(new Block(47 * 32 + 16, (36 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[1]->addSwitchWithBlock(s2);


	findRestartPoint();
}


void Stage32::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);
}

void Stage32::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage32::isClear() const
{
	return !flag->isActive;
}


}
}
}


