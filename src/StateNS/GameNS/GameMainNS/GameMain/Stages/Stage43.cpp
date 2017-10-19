#include "Stage43.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include "..\Gimmick\Torch.h"
#include "..\Gimmick\Door.h"
#include "..\Gimmick\CheckPoint.h"
#include "..\Player\PlayerChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage43::Stage43() :
StageChild(3, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage43::~Stage43()
{
	sound->deleteSound("bgm4");
	sound->deleteSound("boss4");
	DeleteGraph(imageSakuya);
	DeleteGraph(imageNue);
}

void Stage43::initialize()
{

	sound->setSound("Data/Sound/hyakunen.wav", "bgm4");
	sound->setSound("Data/Sound/uno-en.wav", "boss4");
	sound->playSound("bgm4", LOOP, false);

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(43, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(43, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(43, 2, MapPos::POS_LEFT_FREE));

	Door* d = new Door(new Vector2(7 * 32 + 16, 5 * 32 + 16), new Vector2(83 * 32 + 16, 31 * 32 + 16));
	maps[2]->addGimmick(d);


	torches2.push_back(new Torch(9 * 32 + 16, 3 * 32 + 16));
	torches2.push_back(new Torch(42 * 32 + 16, 8 * 32 + 16));
	torches2.push_back(new Torch(71 * 32 + 16, 6 * 32 + 16));
	torches2.push_back(new Torch(10 * 32 + 16, 26 * 32 + 16));
	torches2.push_back(new Torch(71 * 32 + 16, 19 * 32 + 16));
	torches2.push_back(new Torch(84 * 32 + 16, 35 * 32 + 16));
	torches2.push_back(new Torch(6 * 32 + 16, 48 * 32 + 16));
	torches2.push_back(new Torch(30 * 32 + 16, 48 * 32 + 16));
	torches2.push_back(new Torch(68 * 32 + 16, 48 * 32 + 16));

	for (const auto& t : torches2)maps[1]->addDynamicGimmick(t);

	CheckPoint* cp = new CheckPoint(3 * 32 + 16, 5 * 32 + 16, 2);
	this->checkPoints.push_back(cp);
	maps[2]->addGimmick(cp);


	fran = new Fran(95 * 32, 48 * 32, 90 * 32, 40 * 32 + 16);

	startX = 144, startY = 1536;

	flag = new ClearFlag(Vector2(16, 16));
	maps[0]->addGimmick(flag);
	converseFlag0 = true;
	converseFlag1 = true;
	converseFlag1fin = false;
	converseFlag2 = true;
	converseFlag2fin = false;
	vsBoss = false;
	imageSakuya = LoadGraph("Data/Image/Character/haribote_sakuya.png");
	imageNue = LoadGraph("Data/Image/Character/haribote_nueR.png");

	//復活
	bool restart = findRestartPoint();

	//復活したら会話フラグを折る
	if (restart)
	{
		//converseFlag0 = false;
	}
}


void Stage43::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain, _player);
	standardUpdate(_player);
	gameMain->setFilter(FilterType::FILTER_DARK);
//	if(converseFlag0)gameMain->setFilter(FilterType::FILTER_NONE);
//	if(now_stage_num==0)for (const auto& t : torches)if (t->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);
	if (now_stage_num == 0 || now_stage_num == 2)gameMain->setFilter(FilterType::FILTER_NONE);
	if(now_stage_num==1)for (const auto& t : torches2)if (t->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);
}

void Stage43::updateConverse(GameMain* gameMain, PlayerChild* _player)
{
	if (!converseFlag2 && !converseFlag2fin)converseFlag2fin = true;
	//倒したとき
	if (converseFlag2 && !fran->isAlive())
	{
		gameMain->startConverse(432);
		converseFlag2 = false;
	}

	if (!converseFlag1 && !converseFlag1fin)
	{
		this->changeableCharacter |= CHARA_SAKUYA;
		this->changeableCharacter |= CHARA_NUE;
		converseFlag1fin = true;
		sound->stopSound("bgm4");
		sound->playSound("boss4");

	}
	////ボス戦手前の会話
	if (now_stage_num == 2 && converseFlag1 &&_player->getVector2()->y() == 1536)
	{
		vsBoss = true;
		gameMain->startConverse(431);
		converseFlag1 = false;
		fran->setPlayer(_player->getVector2());
		maps[2]->addEnemy(fran);
	}

	////始めの会話
	if (converseFlag0)
	{
		gameMain->startConverse(430);
		converseFlag0 = false;
	}

	if (vsBoss)_player->lockCameraPos(new Vector2(90 * 32, 43 * 32 + 16));

}

void Stage43::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
	if (!converseFlag1 && !converseFlag1fin)DrawRotaGraph(100, 416, 1.0, 0.0, imageNue, TRUE);
	if (!converseFlag1 && !converseFlag1fin)DrawRotaGraph(140, 416, 1.0, 0.0, imageSakuya, TRUE,TRUE);
}

bool Stage43::isClear() const
{
	return converseFlag2fin;
}


}
}
}


