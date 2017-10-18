#include "StageChild.h"
#include "Map.h"

#include "..\Gimmick\CheckPoint.h"
#include "..\Gimmick\Switches\SwitchWithBlock.h"

#include "..\..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


StageChild::StageChild(int _stage_max_x,int _stage_max_y)
{
	stage_max_x = _stage_max_x;
	stage_max_y = _stage_max_y;

	initialize();
	mBackImg = LoadGraph("Data/Image/back11.jpg");
	assert(mBackImg != -1 && "背景画像読み込みエラー");
}

StageChild::~StageChild()
{
	for (auto& map : maps)
	{
		SAFE_DELETE(map);
	}
	maps.clear();
	maps.shrink_to_fit();

	checkPoints.clear();
	checkPoints.shrink_to_fit();
}

void StageChild::initialize()
{
	this->now_stage_num = 0;
	this->changeableCharacter = ChangeableCharacter::CHARA_NONE;
}

void StageChild::standardUpdate(PlayerChild* _player)
{
	maps[now_stage_num]->update(_player, this, false);

	//チェックポイントに来ていてるか確認
	int loop_count = (int)checkPoints.size();
	for (int i = 0; i < loop_count; i++)
	{
		//チェックポイントに来ていたら
		if (checkPoints[i]->visitCheckPoint())
		{
			int switch_flags = 0;

			int loopCount = 0;
			for (int i = 0; i < stage_max_x * stage_max_y; ++i)
			{
				for (const auto& s : maps[i]->getSwitchWithBlocks())
				{
					if (s->isPushed)switch_flags |= (1 << loopCount);
					++loopCount;
				}
			}
			saveData->saveCheckPoint(i, switch_flags);
			break;
		}
	}
}

void StageChild::updateStoppingDynamics(PlayerChild* _player)
{
	maps[now_stage_num]->update(_player, this, true);
}

void StageChild::standardDraw(const Vector2* _camera) const
{
	//背景描画
	int draw_x = (_camera->x() - MyData::CX) / -5;
	int draw_y = (_camera->y() - MyData::CY) / -5;
	DrawGraph(draw_x, draw_y, mBackImg, true);

	maps[now_stage_num]->draw(_camera);

	//for Debug
	if (CheckHitKey(KEY_INPUT_W))
	{
		DrawBox(0, 100, 100, 200, BLACK, true);
		DrawFormatString(10, 110, WHITE, "%d", now_stage_num);
	}

}

void StageChild::draw_front(const Vector2* _camera) const
{
	maps[now_stage_num]->draw_front(_camera);
}

StageChild::ChipType StageChild::getChipType(const Vector2& _other, bool colliWithGimmick) const
{
	return maps[now_stage_num]->getChipType(_other, colliWithGimmick);
}

//ポリモーフィズム
StageChild::ChipType StageChild::getChipType(const Vector2& _other) const
{
	return getChipType(_other, true);
}

//ポリモーフィズム
StageChild::ChipType StageChild::getChipType(const RawVector2& _other, bool colliWithGimmick) const
{
	return getChipType(Vector2(_other.pos_x, _other.pos_y), colliWithGimmick);
}

int StageChild::getTopPosition(const Vector2* _pos, const int& _dy) const
{
	return maps[now_stage_num]->getTopPosition(_pos, _dy);
}

int StageChild::getBottomPosition(const Vector2* _pos, const int& _dy) const
{
	return maps[now_stage_num]->getBottomPosition(_pos, _dy);
}

vector< DynamicGimmickChild* > StageChild::getDynamicGimmicks()
{
	return maps[now_stage_num]->getDynamicGimmicks();
}

vector< SwitchWithBlock* > StageChild::getSwitchWithBlocks()
{
	return maps[now_stage_num]->getSwitchWithBlocks();
}

EnemyController* StageChild::getEController()
{
	return maps[now_stage_num]->getEController();
}

void StageChild::moveStage(HowStageMove _stageMove)
{
	switch (_stageMove)
	{
	case MOVE_RIGHT:
		now_stage_num++;
		break;
	case MOVE_LEFT:
		now_stage_num--;
		break;
	case MOVE_UP:
		now_stage_num -= stage_max_x;
		break;
	case MOVE_DOWN:
		now_stage_num += stage_max_x;
		break;
	}
	assert(now_stage_num < maps.size() && "StageChild: map index out of range!");
}

void StageChild::processDynamcCollision(PlayerChild* _player)
{
	maps[now_stage_num]->processDynamicCollision(_player);
}

void StageChild::addDynamicGimmickToAllMaps(DynamicGimmickChild* _d_gmk)
{
	for (auto& map : maps)
		map->addDynamicGimmick(_d_gmk);
}

//========================================================================
// 内部protected関数
//========================================================================
bool StageChild::findRestartPoint()
{
	int checkIndex = -10;
	int switch_flag = 0;

	saveData->updateCheckPoint(checkIndex, switch_flag);

	//復活できるチェックポイントがあったら
	if (0 <= checkIndex && checkIndex < (int)checkPoints.size())
	{
		CheckPoint*  restartPoint = checkPoints[checkIndex];
		this->now_stage_num = restartPoint->getStageNum();
		this->startX = restartPoint->getX();
		this->startY = restartPoint->getY();

		for (int i = 0; i < stage_max_x * stage_max_y; ++i)
		{
			switch_flag = maps[i]->setSwitchesWithFlag(switch_flag);
		}
		return true;
	}
	return false;
}


//========================================================================
// 内部private関数
//========================================================================




}
}
}


