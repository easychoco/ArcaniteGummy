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



	SwitchWithBlock* s = new SwitchWithBlock(272, 1520);
	s->push_block(new Block(272, 1424, 1.0, BlockType::TYPE_SWITCH), true);
	s->push_block(new Block(304, 1424, 1.0, BlockType::TYPE_LOCK), true);
	maps[0]->addSwitchWithBlock(s);

	/*
	maps[0]->addGimmick(new BeltConveyor(1.0f, Vector2(368, 1552)));
	maps[0]->addGimmick(new BeltConveyor(1.0f, Vector2(400, 1552)));
	maps[0]->addGimmick(new BeltConveyor(1.0f, Vector2(432, 1552)));
	maps[0]->addGimmick(new BeltConveyor(1.0f, Vector2(464, 1552)));

	maps[0]->addEnemy(AllEnemies::ENE_USA, 400, 1520);
	*/

	maps[0]->addGimmick(new Needle(368, 1552, 0.0f));
	maps[0]->addGimmick(new Needle(400, 1552, 0.0f));
	maps[0]->addGimmick(new Needle(432, 1552, 0.0f));
	maps[0]->addGimmick(new Needle(464, 1552, 0.0f));


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


