#include "Stage21.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"
#include "..\Gimmick\Guide.h"
#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage21::Stage21() :
StageChild(3, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage21::~Stage21()
{
	sound->deleteSound("bgm2");
}

void Stage21::initialize()
{
	sound->setSound("Data/Sound/Ousa-sama3.wav", "bgm2");
	sound->playSound("bgm2", LOOP, false);

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(21, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(21, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(21, 2, MapPos::POS_LEFT_FREE));

	vector<string> message
	{
		"妹紅、大丈夫か？",
		"ここでもサポートは",
		"するから",
		"安心してくれ"
	};

	Guide* guide = new Guide(92 * 32 + 16, 48 * 32 + 16, message);
	maps[0]->addGimmick(guide);

	vector<string> message2
	{
		"炎で部屋を",
		"明るくするんだ",
		"私のメッセージを",
		"見られるようにな"
	};

	Guide* guide2 = new Guide(7 * 32 + 16, 48 * 32 + 16, message2);
	maps[1]->addGimmick(guide2);

	vector<string> message3
	{
		"困ったときは",
		"ステージを見回すといい",
		"何かヒントがあるかもな"
	};

	Guide* guide3 = new Guide(61 * 32 + 16, 21 * 32 + 16, message3);
	maps[2]->addGimmick(guide3);


	flag = new ClearFlag(Vector2(3088, 400));
	maps[2]->addGimmick(flag);

	torches.push_back(new Torch(3 * 32 + 16, 48 * 32 + 16));
	torches.push_back(new Torch(42 * 32 + 16, 24 * 32 + 16));
	torches.push_back(new Torch(84 * 32 + 16, 7 * 32 + 16));
	torches.push_back(new Torch(89 * 32 + 16, 34 * 32 + 16));
	for (const auto& t : torches)maps[1]->addDynamicGimmick(t);


	torches2.push_back(new Torch(19 * 32 + 16, 6 * 32 + 16));
	torches2.push_back(new Torch(69 * 32 + 16, 7 * 32 + 16));
	for (const auto& t : torches2)maps[2]->addDynamicGimmick(t);


	startX = 2864, startY = 1536;
	converseFlag0;
	//復活
	bool restart = findRestartPoint();
	//復活したら会話フラグを折る
	if (restart)
	{
		converseFlag0 = false;
	}
}


void Stage21::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain, _player);
	standardUpdate(_player);

	gameMain->setFilter(FilterType::FILTER_DARK);
	if(now_stage_num==0)gameMain->setFilter(FilterType::FILTER_NONE);
	if(now_stage_num==1)for (const auto& t : torches)if (t->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);
	if(now_stage_num==2)for (const auto& t : torches2)if (t->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);

}

void Stage21::updateConverse(GameMain* gameMain,PlayerChild* _player)
{
	if (converseFlag0)
	{
		gameMain->startConverse(210);
		converseFlag0 = false;
	}
}


void Stage21::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage21::isClear() const
{
	return !flag->isActive;
}


}
}
}


