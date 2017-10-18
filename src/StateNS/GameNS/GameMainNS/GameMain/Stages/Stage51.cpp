#include "Stage51.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage51::Stage51() :
StageChild(5, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage51::~Stage51()
{
	sound->deleteSound("bgm5");
	DeleteGraph(imageKaguya);
}

void Stage51::initialize()
{
	sound->setSound("Data/Sound/stage5.wav", "bgm5");
	sound->playSound("bgm5", LOOP, false);
	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;
	this->changeableCharacter |= CHARA_NUE;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(51, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(51, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(51, 2, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(51, 3, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(51, 4, MapPos::POS_LEFT_FREE));

	SwitchWithBlock* s = new SwitchWithBlock(27 * 32 + 16, 19 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)s->push_block(new Block((65 + i) * 32 + 16, 21 * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(s);
	SwitchWithBlock* s1 = new SwitchWithBlock(89 * 32 + 16, 48 * 32 + 16, 1);
	for (int i = 0; i < 3; i++)s1->push_block(new Block((65 + i) * 32 + 16, 23 * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[2]->addSwitchWithBlock(s1);



	flag = new ClearFlag(Vector2(66 * 32 + 16, 26 * 32 + 16));
	maps[2]->addGimmick(flag);
	now_stage_num = 2;
	startX = 144, startY = 1536;
	imageKaguya = LoadGraph("Data/Image/Character/haribote_kaguya.png");
	converseFlag0 = true;
	converseFlag0fin = false;


	findRestartPoint();
}


void Stage51::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain, _player);
	standardUpdate(_player);


}

void Stage51::updateConverse(GameMain* gameMain, PlayerChild* _player)
{
	if (!converseFlag0 && !converseFlag0fin)converseFlag0fin = true;
	if (converseFlag0)
	{
		gameMain->startConverse(510);
		converseFlag0 = false;
	}
}

void Stage51::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
	if (!converseFlag0fin)DrawRotaGraph(320, 240, 1.0, 0.0, imageKaguya, TRUE);

}

bool Stage51::isClear() const
{
	return !flag->isActive;
}


}
}
}


