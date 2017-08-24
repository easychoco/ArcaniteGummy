#include "PlayerChild.h"

#include "..\Stage.h"

//for Debug
#include "..\Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


PlayerChild::PlayerChild(int _x, int _y, float _move, float _jump, int _jumpCount, int _hp) : 
Character(_hp, _x, _y, MyData::PLAYER_CHIP_WIDTH, MyData::PLAYER_CHIP_HEIGHT),
maxMoveSpeed(_move),
maxJumpPower(_jump),
maxJumpCount(_jumpCount)
{
	initialize();
}

void PlayerChild::initialize()
{
	this->moveSpeed = maxMoveSpeed;
	this->jumpPower = 0.0f;
	this->nowJumpCount = 0;
	this->prePush = false;
	this->direction = false;
	this->animationTime = 0;

	post_x = MyData::MAP_WIDTH / 2;
	post_y = MyData::MAP_HEIGHT / 2;

}

void PlayerChild::draw() const
{
	
	int draw_x = 320 + (p->pos_x() - camera->pos_x()) / MyData::vectorRate;
	int draw_y = 240 + (p->pos_y() - camera->pos_y()) / MyData::vectorRate;

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, direction);
	DrawCircle(draw_x, draw_y, 5, MyData::GREEN, true);

	draw_other();
	draw_changingAnimation(draw_x, draw_y);

	//for Debug
	DrawBox(60, 20, 60 + hpController.getHP() * 5, 50, MyData::GREEN, true);
	DrawFormatString(0, 50, MyData::BLACK, "%d %d", p->x(), p->y());
	DrawFormatString(0, 70, MyData::BLACK, "%d %d", collision->p->x(), collision->p->y());
}


//================================================
//内部protected関数
//================================================
void PlayerChild::standardAction(const Stage* _stage)
{
	move(_stage);
	changeCharacter();
	processDamage();
}

//変更アニメーションが終わってキャラ変更できるかどうか
bool PlayerChild::canChangeCharacter()
{
	return animationTime > 30;
}



//================================================
//内部private関数
//================================================

//キャラ変更アニメーション
void PlayerChild::changeCharacter(/*Charaのenum next*/)
{
	if (Input_CHANGE())
	{
		animationTime = max(animationTime, 1);
	}
	if (animationTime == 0)return;

	++animationTime;
}

void PlayerChild::draw_changingAnimation(int _draw_x, int _draw_y) const
{
	if (animationTime == 0)return;
	DrawCircle(_draw_x, _draw_y, animationTime * 2, MyData::WHITE);
}

void PlayerChild::processDamage()
{
	if (damaged)
	{
		++damagedTime;
		if(damagedTime < 3)hittedAction();
		if (damagedTime > 60)
		{
			damaged = false;
			damagedTime = 0;
		}
	}
}

void PlayerChild::hittedAction()
{
	//ノックバック
	float dx = direction ? 10.0f : -10.0f;
	this->moveCharacter(dx, 0.0f);
}

//移動
void PlayerChild::move(const Stage* _stage)
{
	//キャラ交代中ならreturn
	if (animationTime > 0)return;

	int dx = next_dx;
	int dy = next_dy;

	next_dx = next_dy = 0;

	//入力
	if (Input_RIGHT())dx += (int)(moveSpeed * MyData::vectorRate);
	if (Input_LEFT())dx -= (int)(moveSpeed * MyData::vectorRate);

	//地上にいるなら
	if (jumpPower == 0 && isOnGround(_stage))
	{
		nowJumpCount = 0;
	}

	//ジャンプ
	if (Input_JUMP() && !prePush && nowJumpCount < maxJumpCount)
	{
		jumpPower = maxJumpPower;
		nowJumpCount++;
	}

	//縦移動
	dy += gravity() - jump();

	dx = getHorizontalDiffer(_stage, dx);
	dy = jumpPower > 0.5f ? getTopDiffer(_stage, dy) : getBottomDiffer(_stage, dy);

	//天井に当たったら
	if (abs(dy) <= 1000)jumpPower = 0;

	p->raw_x += dx;
	p->raw_y += dy;

	int dx_onScreen = p->x() - post_x;
	int dy_onScreen = p->y() - post_y;

	nextStageMove = GameMain::MOVE_NONE;
	if (dx_onScreen < -MyData::MAP_WIDTH / 2)
	{
		nextStageMove = GameMain::MOVE_RIGHT;
	}
	else if (dx_onScreen > MyData::MAP_WIDTH / 2)
	{
		nextStageMove = GameMain::MOVE_LEFT;
	}
	else if (dy_onScreen > MyData::MAP_HEIGHT / 2)
	{
		nextStageMove = GameMain::MOVE_UP;
	}
	else if (dy_onScreen < -MyData::MAP_HEIGHT / 2)
	{
		nextStageMove = GameMain::MOVE_DOWN;
	}

	post_x = p->x();
	post_y = p->y();


	//カメラ位置を更新	
	*camera = Vector2(
		max(320, min(MyData::MAP_WIDTH  - 320, p->x())),
		max(240, min(MyData::MAP_HEIGHT - 240, p->y()))
	);
	
	prePush = Input_JUMP();
}

bool PlayerChild::isOnGround(const Stage* _stage)
{
	//posはキャラの最下端よりひとつ下
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate);
	
	
	//右上に向けた斜めブロックなら
	if (chipType == Stage::ChipType::TYPE_DOWN_SLANT_RIGHT)
	{
		pos.pos_y -= (MyData::CHIP_WIDTH_RATE() - p->pos_x() % MyData::CHIP_WIDTH_RATE());
		chipType = _stage->getChipType(pos / MyData::vectorRate);
	}

	//左上に向けた斜めブロックなら
	else if (chipType == Stage::ChipType::TYPE_DOWN_SLANT_LEFT)
	{
		pos.pos_y -= p->pos_x() % MyData::CHIP_WIDTH_RATE();
		chipType = _stage->getChipType(pos / MyData::vectorRate);
	}

	return chipType != Stage::ChipType::TYPE_BACK;
}

//ジャンプでの移動量を返す
//正の値で上方向
int PlayerChild::jump()
{
	jumpPower = max(0.0f, jumpPower - 1.0f);
	return (int)(jumpPower * MyData::vectorRate);
}

//かかる重力を返す
//正の値で下方向
int PlayerChild::gravity()
{
	//for Debug
	//このままいくならconstexprで
	return 7 * MyData::vectorRate;
}


}
}
}