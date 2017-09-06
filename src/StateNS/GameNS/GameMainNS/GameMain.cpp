#include "GameMain.h"

#include "Converse.h"

#include "GameMain\Stage.h"
#include "GameMain\System.h"
#include "GameMain\Player\Mokou.h"
#include "GameMain\Player\Sakuya.h"

#include "GameMain\Enemy\EnemyController.h"
#include "GameMain\Enemy\EnemyChild.h"

#include "GameMain\Gimmick\DynamicGimmickChild.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


GameMain::GameMain(){
	initialize();
}

GameMain::~GameMain()
{
	for (auto& stage : mStages)
	{
		SAFE_DELETE(stage);
	}
	mStages.clear();
	mStages.shrink_to_fit();

	SAFE_DELETE(mPlayer);
	SAFE_DELETE(mSystem);
	SAFE_DELETE(mEController);
}

void GameMain::initialize()
{
	//for Debug
	for (int i = 0; i <= 2; i++)
	{
		mStages.push_back(new Stage(0, i));
	}

	//ステージの全体的な縦と横の数を設定
	//TODO なんで設定したんだっけ...？
	for (auto& stage : mStages)
	{
		stage->setStageSize(3, 1);//よこ、たて
	}
	nowStageNum = 0;

	mPlayer = new Sakuya(96, 1500, 100);
	mSystem = new System(nowStageNum);
	mEController = new EnemyController();

	changed = false;
}

Child* GameMain::update(GameParent* _parent)
{
	Child* next = this;

	//今のstageを設定
	nowStageNum = mSystem->getNowStage();
	Stage* stage = mStages[nowStageNum];

	//Stageのupdate
	stage->update(mPlayer);

	//Playerのupdate
	PlayerChild* nextPlayer = mPlayer->update(stage);
	changed = false;
	if (nextPlayer != mPlayer)
	{
		SAFE_DELETE(mPlayer);
		mPlayer = nextPlayer;
		changed = true;
	}

	//enemyのupdate
	mEController->update(stage);

	//衝突判定
	processCollision(stage);

	//for Debug
	mPlayer->hpController.recover(1);

	//Systemのupdate
	if(changed)mSystem->update(HowStageMove::MOVE_NONE);
	else mSystem->update(mPlayer->getStageMove());

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		next = new Converse(this, 1,1);
	
	return next;
}

void GameMain::draw() const
{
	//if (changed)return;

	//DrawFormatString(0, 20, MyData::WHITE, "GameMain");
	mStages[nowStageNum]->draw(mPlayer->getCamera());
	mEController->draw(mPlayer->getCamera());
	mPlayer->draw();
	mSystem->draw();
}


//==============================================
//内部プライベート関数
//==============================================

void GameMain::processCollision(Stage* _stage)
{
	//TODO -> 高速化したい
	//違うステージのものは処理しないとか

	//敵
	auto enemies = mEController->getEnemies();

	//プレイヤーの攻撃
	auto p_attacks = mPlayer->getAtacks();

	//敵の攻撃
	//...

	for (auto& enemy : enemies)
	{
		if (!enemy->isAlive())continue;

		//プレイヤーと敵の衝突
		if (mPlayer->isHit(enemy))
		{
			mPlayer->hpController.damage(5);
		}

		//プレイヤーの攻撃と敵の衝突
		for (auto& attack : p_attacks)
		{
			if (attack->isActive)
			{
				if (attack->isHit(enemy))
				{
					enemy->hpController.damage(attack->getDamageValue());
					attack->hittedAction();

				}
			}
		}
	}

	//DynamicGimmick
	auto d_gimmicks = _stage->getDynamicGimmicks();

	for (auto& gimmick : d_gimmicks)
	{
		if (!gimmick->isActive)continue;

		//プレイヤーとDynamicGimmickの衝突
		if (mPlayer->isHit(gimmick))
		{

		}

		//プレイヤーの攻撃とDynamicGimmickの衝突
		//プレイヤーの攻撃と敵の衝突
		for (auto& attack : p_attacks)
		{
			if (attack->isActive)
			{
				if (attack->isHit(gimmick))
				{
					gimmick->hittedAction();
					attack->hittedAction();

					if(attack->id == ObjectID::A_FIRE)
						gimmick->burnedAction();
				}
			}
		}

	}

}

}
}
}