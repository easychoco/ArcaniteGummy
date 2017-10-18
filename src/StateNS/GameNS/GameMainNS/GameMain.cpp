#include "GameMain.h"

#include "Converse.h"
#include "Pause.h"

#include "GameMain\Stages\StageChild.h"
#include "GameMain\Stages\AllStages.h"
#include "GameMain\System.h"
#include "GameMain\Player\Mokou.h"
#include "GameMain\Player\Sakuya.h"
#include "GameMain\Player\Nue.h"

#include "GameMain\Enemy\EnemyController.h"
#include "GameMain\Enemy\EnemyChild.h"

#include "GameMain\Gimmick\DynamicGimmickChild.h"
#include "GameMain\Gimmick\Block.h"
#include "GameMain\Gimmick\Switches\SwitchWithBlock.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{


GameMain::GameMain(int _n)
{
	stageID = _n;
	initialize();
}

GameMain::~GameMain()
{
	SAFE_DELETE(mStage);
	SAFE_DELETE(mPlayer);
	SAFE_DELETE(mSystem);

	DeleteGraph(icon_mokou);
	DeleteGraph(icon_sakuya);
	DeleteGraph(icon_nue);

	sound->deleteSound("jump");
	sound->deleteSound("damage");
	sound->deleteSound("change");
	sound->deleteSound("damage_enemy");
	sound->deleteSound("break_enemy");
}

void GameMain::initialize()
{
	mStage = getNextStage(stageID);

	//最初のキャラを設定
	int changeableCharacter = mStage->getChangeableCharacter();
	if (changeableCharacter & StageChild::ChangeableCharacter::CHARA_MOKOU)
	{
		mPlayer = new Mokou(mStage->startX, mStage->startY, PLAYER_MAX_HP);
	}
	else if (changeableCharacter & StageChild::ChangeableCharacter::CHARA_SAKUYA)
	{
		mPlayer = new Sakuya(mStage->startX, mStage->startY, PLAYER_MAX_HP);
	}
	else if (changeableCharacter & StageChild::ChangeableCharacter::CHARA_NUE)
	{
		mPlayer = new Nue(mStage->startX, mStage->startY, PLAYER_MAX_HP);
	}
	else
	{
		assert(!"使用キャラを設定してください");
	}

	if (mPlayer->hasAdditionalGimmick())
		mStage->addDynamicGimmickToAllMaps(mPlayer->getAdditionalGimmick());


	mSystem = new System();

	mEController = mStage->getEController();
	mEController->setPlayerPos(mPlayer->getVector2());

	mTime = 0;
	converseNum = 0;

	stopDynamicObject = StopType::TYPE_NONE;
	nextCharacter = PlayerCharacter::CHARA_NONE;

	//HPバーに描く画像をロード
	icon_mokou = LoadGraph("Data/Image/icon_mokou.png");
	assert(icon_mokou != -1 && "icon_mokou読み込みエラー");

	icon_sakuya = LoadGraph("Data/Image/icon_sakuya.png");
	assert(icon_sakuya != -1 && "icon_sakuya読み込みエラー");

	icon_nue = LoadGraph("Data/Image/icon_nue.png");
	assert(icon_nue != -1 && "icon_nue読み込みエラー");

	//Player共通で使うサウンドを設定
	sound->setSound("Data/Sound/jump.mp3", "jump");
	sound->setSound("Data/Sound/damage.mp3", "damage");
	sound->setSound("Data/Sound/change.mp3", "change");
	sound->setSound("Data/Sound/damage_enemy.wav", "damage_enemy");
	sound->setSound("Data/Sound/break_enemy.mp3", "break_enemy");
}

Child* GameMain::update(GameParent* _parent)
{
	Child* next = this;
	++mTime;
	
	//マップ移動していたら
	StageChild::HowStageMove nextMove = mPlayer->getStageMove();
	if (nextMove != StageChild::HowStageMove::MOVE_NONE)
	{
		mStage->moveStage(mPlayer->getStageMove());
		this->mEController = mStage->getEController();
		mEController->setPlayerPos(mPlayer->getVector2());
	}

	//for Debug
	if(Input_W())mPlayer->hpController.recover(10000000);
	

	//時が止まっているか更新
	stopDynamicObject = mPlayer->getStopDynamicObject();

	//DynamicObjectを更新
	if(stopDynamicObject == StopType::TYPE_NONE)updateDynamics(mStage);

	//咲夜の時止め中でも効果のあるギミックを更新
	else if (stopDynamicObject == StopType::TYPE_SAKUYA)updateStoppingDynamics(mStage);

	//Playerのupdate
	PlayerChild* nextPlayer = mPlayer->update(mStage);

	//外部からのキャラ変更
	if (nextCharacter != CHARA_NONE)
	{
		int x = mPlayer->getVector2()->x();
		int y = mPlayer->getVector2()->y();

		switch (nextCharacter)
		{
		case CHARA_MOKOU: nextPlayer = new Mokou(x, y, mPlayer->hpController.getHP()); break;
		case CHARA_SAKUYA: nextPlayer = new Sakuya(x, y, mPlayer->hpController.getHP()); break;
		case CHARA_NUE: nextPlayer = new Nue(x, y, mPlayer->hpController.getHP()); break;
		}
	}

	//for Debug
	//リジェネ
	if (Input_W())mPlayer->hpController.recover(10000);

	//Player交代
	if (nextPlayer != mPlayer)
	{
		SAFE_DELETE(mPlayer);
		mPlayer = nextPlayer;

		//ぬえのUFOを追加
		if(mPlayer->hasAdditionalGimmick())
			mStage->addDynamicGimmickToAllMaps(mPlayer->getAdditionalGimmick());

		//EnemyControllerを更新
		this->mEController = mStage->getEController();
		mEController->setPlayerPos(mPlayer->getVector2());
	}

	if (!mPlayer->hpController.isAlive())_parent->moveTo(_parent->SEQ_OVER);

	//衝突判定
	processCollision(mStage);

	//Systemのupdate
	mSystem->update();

	//会話パート
	if(converseNum != 0)
		next = new Converse(this, converseNum);
	converseNum = 0;
	
	//ポーズ
	if (Input_A() && mTime > 10)
	{
		next = new Pause(this);
		mTime = 0;
	}

	//クリア
	if (mStage->isClear())
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
	mStage->draw(mPlayer->getCamera());
	mEController->draw(mPlayer->getCamera());

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	mPlayer->draw();

	mStage->draw_front(mPlayer->getCamera());

	mSystem->draw(mPlayer->getVector2());

	drawPlayerInfo();
}

void GameMain::setFilter(FilterType _f) { mSystem->setFilter(_f); }

const Vector2* GameMain::getCameraPos() const
{
	return mPlayer->getCamera(); 
}

void GameMain::moveCamera(int _dx, int _dy)
{
	mPlayer->moveCamera(_dx, _dy);
}

void GameMain::setCamera(const Vector2& _camera)
{
	mPlayer->setCamera(_camera);
}

void GameMain::setNextCharacter(PlayerCharacter _next)
{
	nextCharacter = _next;
}

//==============================================
//内部プライベート関数
//==============================================
void GameMain::updateDynamics(StageChild* stage)
{
	//enemyのupdate
	mEController->update(stage, mPlayer->getCamera());

	//Stageのupdate
	stage->update(this, mPlayer);
}

void GameMain::updateStoppingDynamics(StageChild* stage)
{
	stage->updateStoppingDynamics(mPlayer);
}

void GameMain::processCollision(StageChild* _stage)
{
	//自機とDynamicGimmickの衝突
	mStage->processDynamcCollision(mPlayer);

	//敵
	auto enemies = mEController->getEnemies();

	//プレイヤーの攻撃
	auto p_attacks = mPlayer->getAttacks();

	//敵の攻撃
	//mEController->processCollision(mPlayer);

	for (auto& enemy : enemies)
	{
		if (!enemy->isAlive())continue;

		//プレイヤーと敵の衝突
		if (mPlayer->isHit(enemy))
		{
			mPlayer->hpController.damage(5);
		}

		//敵の攻撃とプレイヤーの衝突
		//敵にChildがある場合はEnemyChildの方で対応済み
		for (auto& eAttack : enemy->getAttacks())
		{
			if (eAttack->isActive && mPlayer->isHit(eAttack)) 
			{
				mPlayer->hpController.damage(eAttack->getDamageValue());
			}
		}

		//プレイヤーの攻撃と敵の衝突
		for (auto& attack : p_attacks)
		{
			if (attack->isActive)
			{
				if (attack->isHit(enemy))
				{
					enemy->hpController.damage(attack->getDamageValue());
					enemy->hittedAction();
					attack->hittedAction();
				}
				//敵がComposite等で本体以外にも実態を持っていたら
				if (enemy->hasChild)
				{
					for (auto& eChild : enemy->getChilds())
					{
						if (attack->isHit(eChild))
						{
							eChild->hpController.damage(attack->getDamageValue());
							eChild->hittedAction();
							attack->hittedAction();
						}
					}
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
		if (gimmick->isOverlap(mPlayer->getVector2()))
		{
			gimmick->apply(mPlayer);
		}

		//プレイヤーの攻撃とDynamicGimmickの衝突
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
	}
}

StageChild* GameMain::getNextStage(int stageID)
{
	
	if (stageID == 11)return new Stage11();
	if (stageID == 12)return new Stage12();
	if (stageID == 13)return new Stage13();
	if (stageID == 21)return new Stage21();
	if (stageID == 22)return new Stage22();
	if (stageID == 23)return new Stage23();
	if (stageID == 31)return new Stage31();
	if (stageID == 32)return new Stage32();
	if (stageID == 33)return new Stage33();
	if (stageID == 41)return new Stage41();
	if (stageID == 42)return new Stage42();
	if (stageID == 43)return new Stage43();
	if (stageID == 51)return new Stage51();
	if (stageID == 52)return new Stage52();
	if (stageID == 53)return new Stage53();

	//for Debug
	if (stageID == 0)return new Stage00();

	//ここにはこない
	assert(!"GameMain::getNextStage 不正なStageID");
	return NULL;
}

void GameMain::drawPlayerInfo() const
{
	//枠を書く
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(30, 10, 50 + PLAYER_MAX_HP * 2, 60, BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	//残りHPを数値で表示
	DrawFormatString(38, 15, WHITE, "HP: %d / %d", mPlayer->hpController.getHP(), PLAYER_MAX_HP);

	//残りHPをバーで表示
	DrawBox(38, 38, 42 + PLAYER_MAX_HP * 2, 52, WHITE, false);
	DrawBox(40, 40, 40 + mPlayer->hpController.getHP() * 2, 50, MyData::GREEN, true);

	//交代可能なアイコンを表示
	if(mStage->canChangeCharacter(mStage->ChangeableCharacter::CHARA_MOKOU, false))DrawGraph(320, 10, icon_mokou, true);
	if(mStage->canChangeCharacter(mStage->ChangeableCharacter::CHARA_SAKUYA, false))DrawGraph(360, 10, icon_sakuya, true);
	if(mStage->canChangeCharacter(mStage->ChangeableCharacter::CHARA_NUE, false))DrawGraph(400, 10, icon_nue, true);


}


}
}
}