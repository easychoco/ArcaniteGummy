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
	//雲のエフェクトを横に流れるようにする
	this->drawEffect = true;
	this->backDrawType = DRAW_HORIZONTAL;
	this->setEffectImage("Data/Image/effect_cloud.png");

	this->setBackImage("Data/Image/back1.jpg");

	sound->setSound("Data/Sound/stage1.wav", "bgm1");
	sound->setVolume("bgm1", sound->allVolume * 0.7f);
	sound->playSound("bgm1", LOOP, false);

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;
	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(11, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(11, 1, MapPos::POS_LEFT_FREE));

	vector<string> message
	{
		"妹紅のサポートは",
		"私、上白沢慧音に",
		"任せてくれ",
		"分からないことがあったら",
		"立て看板を見てくれ",
	};

	Guide* guide = new Guide(272, 1552, message);
	maps[0]->addGimmick(guide);

	vector<string> message2
	{
		"ゴールフラグだ",
		"これを取れば",
		"ステージクリアだぞ",
	};

	Guide* guide2 = new Guide(89*32+16, 39*32+16, message2);
	maps[1]->addGimmick(guide2);

	vector<string> message3
	{
		"炎で攻撃して",
		"敵を倒すんだ",
		"残念ながら",
		"踏みつけることはできない",
	};

	Guide* guide3 = new Guide(18 * 32 + 16, 47 * 32 + 16, message3);
	maps[0]->addGimmick(guide3);

	vector<string> message4
	{
		"妹紅は二段ジャンプが",
		"できるから",
		"高い足場に届くぞ"
	};

	Guide* guide4 = new Guide(31 * 32 + 16, 48 * 32 + 16, message4);
	maps[0]->addGimmick(guide4);

	vector<string> message5
	{
		"ダッシュして",
		"一気に駆け抜けることもできるぞ"
	};

	Guide* guide5 = new Guide(47 * 32 + 16, 48 * 32 + 16, message5);
	maps[0]->addGimmick(guide5);

	vector<string> message6
	{
		"いろんな種類の敵がいるから",
		"注意が必要だな"
	};

	Guide* guide6 = new Guide(8 * 32 + 16, 45 * 32 + 16, message6);
	maps[1]->addGimmick(guide6);



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


