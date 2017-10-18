#include "Stage53.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include "..\Enemy\Kaguya.h"
#include "..\Enemy\EnemyController.h"
#include "..\Player\PlayerChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage53::Stage53() :
StageChild(1, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage53::~Stage53()
{
	sound->deleteSound("bgm5");
	sound->deleteSound("boss5");
}

void Stage53::initialize()
{
	sound->setSound("Data/Sound/stage5.wav", "bgm5");
	sound->setSound("Data/Sound/taketori.wav", "boss5");
	sound->playSound("bgm5", LOOP, false);
	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;
	this->changeableCharacter |= CHARA_NUE;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(53, 0, MapPos::POS_SINGLE));


	//輝夜設定
	kaguya = new Kaguya(95 * 32, 48 * 32);

	converseFlag0 = true;
	converseFlag1 = true;
	converseFlag0fin = false;
	converseFlag1fin = false;

	now_stage_num = 0;
	startX = 84*32, startY = 48*32;
	findRestartPoint();

}


void Stage53::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain, _player);
	standardUpdate(_player);

	//暗闇にする
	if (kaguya->makeDark())
	{
		gameMain->setFilter(FilterType::FILTER_DARK);
	}
	else
	{
		gameMain->setFilter(FilterType::FILTER_NONE);
	}

	//輝夜が敵を生成する
	if (kaguya->makeEnemy())
	{
		kaguya->setMuteki(true);
		for (int i = 0; i < kaguya->maxCreateEnemyNum; i++)
		{
			int ene_num = GetRand(5);

			//地上の敵
			if (ene_num <= 3)
			{
				maps[0]->addEnemy(itoE(ene_num), _player->getVector2(), kaguya->getVector2()->x(), kaguya->getVector2()->y() + 16);
			}
			else
			{
				maps[0]->addEnemy(itoE(ene_num), _player->getVector2(), kaguya->getVector2()->x(), kaguya->getVector2()->y() - 100);
			}
		}
	}
	auto enes = maps[0]->getEController()->getEnemies();

	//輝夜以外に敵がいるなら
	if (maps[0]->getEController()->getEnemies().size() != 1)
	{
		maps[0]->getEController()->minimize_enemies();

		//サイズが1になっていたら
		if(maps[0]->getEController()->getEnemies().size() == 1)kaguya->setMuteki(false);
	}
}

void Stage53::updateConverse(GameMain* gameMain, PlayerChild* _player)
{

	if (!converseFlag1 && !converseFlag1fin)converseFlag1fin = true;
	if (converseFlag1 && !kaguya->isAlive())
	{
		gameMain->startConverse(531);
		converseFlag1 = false;
	}



	if (!converseFlag0 && !converseFlag0fin) 
	{
		converseFlag0fin = true;
		sound->stopSound("bgm5");
		sound->playSound("boss5");
	}
	if (converseFlag0)
	{
		_player->lockCameraPos(new Vector2(90 * 32, 43 * 32));
		kaguya->setPlayer(_player->getVector2());
		maps[0]->addEnemy(kaguya);
		gameMain->startConverse(530);
		converseFlag0 = false;
	}

}

void Stage53::draw(const Vector2* _camera) const
{

	standardDraw(_camera);
}

void Stage53::draw_front(const Vector2* _camera)const
{
	if (converseFlag0)DrawBox(0, 0, 640, 480, BLACK, TRUE);

}

bool Stage53::isClear() const
{
	return converseFlag1fin;
}


}
}
}


