#include "GameMain.h"

#include "Converse.h"

#include "GameMain\Stage.h"
#include "GameMain\System.h"
#include "GameMain\Player\Mokou.h"
#include "GameMain\Player\Sakuya.h"
#include "GameMain\Player\Nue.h"

#include "GameMain\Enemy\EnemyController.h"
#include "GameMain\Enemy\EnemyChild.h"

#include "GameMain\Gimmick\DynamicGimmickChild.h"
#include "GameMain\Gimmick\Block.h"
#include "GameMain\Gimmick\Switches\SwitchWithBlock.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


GameMain::GameMain(int _n,int _x,int _y){
	xNum = _x, yNum = _y;
	stageID = _n;
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
	for (int i = 0; i < xNum * yNum; i++)
	{
		mStages.push_back(new Stage(stageID, i, xNum - 1, yNum - 1));
	}

	//ステージの全体的な縦と横の数を設定

	//TODO 数値をファイルより取得
	int stage_x = 2;
	int stage_y = 1;
	nowStageNum = 0;

	mPlayer = new Nue(96, 1500, 100);
	mSystem = new System(nowStageNum, xNum, yNum);

	mEController = new EnemyController();
	mEController->setPlayerPos(mPlayer->getVector2());

	stopDynamicObject = StopType::TYPE_NONE;
}

Child* GameMain::update(GameParent* _parent)
{
	Child* next = this;

	//今のstageを設定
	nowStageNum = mSystem->getNowStage();
	Stage* stage = mStages[nowStageNum];

	//時が止まっているか更新
	stopDynamicObject = mPlayer->getStopDynamicObject();

	//DynamicObjectを更新
	if(stopDynamicObject == StopType::TYPE_NONE)updateDynamics(stage);

	//Playerのupdate
	PlayerChild* nextPlayer = mPlayer->update(stage);

	//Player交代
	if (nextPlayer != mPlayer)
	{
		SAFE_DELETE(mPlayer);
		mPlayer = nextPlayer;
		mEController->setPlayerPos(mPlayer->getVector2());
	}

	//衝突判定
	processCollision(stage);

	//for Debug
	mPlayer->hpController.recover(1);

	//Systemのupdate
	mSystem->update(mPlayer->getStageMove());

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		next = new Converse(this, 1,1);
	
	//クリア
	if (stage->isClear())
	{
		_parent->moveTo(_parent->NextSequence::SEQ_CLEAR);
	}

	return next;
}

void GameMain::draw() const
{
	if (stopDynamicObject == StopType::TYPE_SAKUYA)
	{
		DrawBox(0, 0, 640, 480, WHITE, true);
		SetDrawBlendMode(DX_BLENDMODE_SUB, 200);
	}
	mStages[nowStageNum]->draw(mPlayer->getCamera());
	mEController->draw(mPlayer->getCamera());

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	mPlayer->draw();
	mSystem->draw(mPlayer->getVector2());
}



//==============================================
//内部プライベート関数
//==============================================
void GameMain::updateDynamics(Stage* stage)
{
	//Stageのupdate
	stage->update(mPlayer);

	//enemyのupdate
	mEController->update(stage);
}

void GameMain::processCollision(Stage* _stage)
{
	//TODO -> 高速化したい
	//違うステージのものは処理しないとか

	//敵
	auto enemies = mEController->getEnemies();

	//プレイヤーの攻撃
	auto p_attacks = mPlayer->getAttacks();

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
			if (attack->isActive && attack->isHit(gimmick))
			{
				gimmick->hittedAction();
				attack->hittedAction();

				if (attack->id == ObjectID::A_FIRE)
					gimmick->burnedAction();
			}
		}

		auto s_b = _stage->getSwitchWithBlocks();

		//TODO ネスト減らしたい
		for (auto& s : s_b)
		{
			for (auto& attack : p_attacks)
			{
				if (attack->isActive && attack->isHit(s))
				{
					s->hittedAction();
					attack->hittedAction();
					s->checkOnActiveArea(attack->getVector2());
				}
			}
		}
	}
}


}
}
}