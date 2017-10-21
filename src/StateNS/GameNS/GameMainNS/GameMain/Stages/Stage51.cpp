#include "Stage51.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"
#include "..\Gimmick\CheckPoint.h"
#include "..\Player\PlayerChild.h"

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
	sound->setSound("Data/Sound/bgm_maoudamashii_neorock73.ogg", "bgm5");
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

	CheckPoint* cp = new CheckPoint(63 * 32 + 16, 20 * 32 + 16, 2);
	this->checkPoints.push_back(cp);
	maps[2]->addGimmick(cp);


	flag = new ClearFlag(Vector2(66 * 32 + 16, 26 * 32 + 16));
	maps[2]->addGimmick(flag);
	now_stage_num = 2;
	startX = 144, startY = 1536;
	imageKaguya = LoadGraph("Data/Image/haribote_kaguya.png");
	converseFlag0 = true;
	converseFlag0fin = false;
	time = 0;
	//復活
	bool restart = findRestartPoint();
	//復活したら会話フラグを折る
	if (restart)
	{
		converseFlag0 = false;
		converseFlag0fin = true;
	}
}


void Stage51::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain, _player);
	standardUpdate(_player);
//	time++;
//	if (time % 360 == 0)for (int i = 0; i < 2; i++)maps[3]->addEnemy(ENE_ICE, _player->getVector2(), (36 + (i * 2)) * 32, 1 * 32);
	//一気に落ちてくるからやめた方がいい気がする

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
	if (!converseFlag0fin)DrawRotaGraph(320, 416, 1.0, 0.0, imageKaguya, TRUE);

}

bool Stage51::isClear() const
{
	return !flag->isActive;
}


}
}
}


