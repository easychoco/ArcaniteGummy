#include "Stage11.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"
#include "..\Gimmick\Guide.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage11::Stage11() :
StageChild(2, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage11::~Stage11()
{
	sound->deleteSound("bgm1");
}

void Stage11::initialize()
{
	this->mBackImg = LoadGraph("Data/Image/back1.jpg");
	sound->setSound("Data/Sound/stage1.wav", "bgm1");
	sound->playSound("bgm1", LOOP, false);

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(11, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(11, 1, MapPos::POS_LEFT_FREE));

	//this->maps[0]->addEnemy(BOSS_JUNKO, 540, 1488);
	/*
	vector<string> message
	{
		"        ガイド例",
		"           ∧_∧",
		"          (*ﾟーﾟ) ＿＿＿＿",
		"           / つ／ | ／ |",
		"    ～　　 | ￣￣￣￣ | . |",
		" ､､､､（/　 | AAも可能 | ／, , , , ,",
	};
	*/
	vector<string> message
	{
		"妹紅のサポートは",
		"私、上白沢慧音に",
		"任せてくれ",
		"分からないことがあったら",
		"手を挙げるんだぞ",
	};

	Guide* guide = new Guide(272, 1552, message);
	maps[0]->addGimmick(guide);


	flag = new ClearFlag(Vector2(3056, 1264));
	maps[1]->addGimmick(flag);
	
	startX = 144, startY = 1536;
	converseFlag0 = true;

	//復活
	bool restart = findRestartPoint();
	//復活したら会話フラグを折る
	if (restart)
	{
		converseFlag0 = false;
	}
}


void Stage11::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain, _player);
	standardUpdate(_player);
}

void Stage11::updateConverse(GameMain* gameMain, PlayerChild* _player)
{
	if (converseFlag0)
	{
		gameMain->startConverse(110);
		converseFlag0 = false;
	}
}

void Stage11::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage11::isClear() const
{
	return !flag->isActive;
}


}
}
}


