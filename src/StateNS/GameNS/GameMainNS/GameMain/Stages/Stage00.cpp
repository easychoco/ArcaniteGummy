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
	
	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;
	this->changeableCharacter |= CHARA_NUE;

	flag = new ClearFlag(Vector2(3056, 1264));
	maps[1]->addGimmick(flag);

	CheckPoint* cp = new CheckPoint(816, 1488, 0);
	checkPoints.push_back(cp);
	maps[0]->addGimmick(cp);

	CheckPoint* cp2 = new CheckPoint(496, 1168, 1);
	checkPoints.push_back(cp2);
	maps[1]->addGimmick(cp2);

	SwitchWithBlock* s = new SwitchWithBlock(20 * 32 + 16, 40 * 32 + 16);
	for (int i = 0; i < 8; i++)s->push_block(new Block((75 + i) * 32 + 16, 38 * 32 + 16, 1.0, BlockType::TYPE_SWITCH), true);
	maps[0]->addSwitchWithBlock(s);

	SwitchWithBlock* s2 = new SwitchWithBlock(20 * 32 + 16, 34 * 32 + 16);
	for (int i = 0; i < 8; i++)s2->push_block(new Block(42 * 32 + 16, (37 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[0]->addSwitchWithBlock(s2);

	SwitchWithBlock* s3 = new SwitchWithBlock(20 * 32 + 16, 40 * 32 + 16);
	for (int i = 0; i < 8; i++)s3->push_block(new Block(42 * 32 + 16, (37 + i) * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[1]->addSwitchWithBlock(s3);



	startX = 144, startY = 1536;

	findRestartPoint();
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


