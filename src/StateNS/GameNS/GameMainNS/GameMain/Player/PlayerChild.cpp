#include "PlayerChild.h"

#include "..\Stage.h"

//for Debug
#include "..\Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

PlayerChild::PlayerChild(int _x, int _y, float _move, float _jump, int _jumpCount, int _hp) :
Character(_hp, _x, _y, MyData::PLAYER_CHIP_WIDTH, MyData::PLAYER_CHIP_HEIGHT, _jump, _jumpCount),
maxMoveSpeed(_move)
{
	post_x = _x;
	post_y = _y;
	this->camera = new Vector2(_x, _y);

	initialize();
	assert(*mImage != -1 && "自機画像読み込みエラー");
}

PlayerChild::~PlayerChild()
{
	SAFE_DELETE(camera);

	for (auto& a : attacks)
	{
		SAFE_DELETE(a);
	}
	attacks.clear();
	attacks.shrink_to_fit();
}

void PlayerChild::initialize()
{
	this->moveSpeed = maxMoveSpeed;
	this->jumpPower = 0.0f;
	this->nowJumpCount = 0;
	this->prePush = false;
	this->direction = false;
	this->animationTime = 0;
	this->animeNum = 0;
	this->animeCount = 0;
	this->onGround = false;
	this->onLadder = false;
	this->actionState = ACT_NORMAL;

	updateCamera();
}

void PlayerChild::draw() const
{
	int draw_x = MyData::CX + (p->x() - camera->x());
	int draw_y = MyData::CY + (p->y() - camera->y());

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage[animeNum], true);

	draw_other();
	draw_changingAnimation(draw_x, draw_y);

	//hpController.draw();
	//for Debug
	DrawBox(60, 20, 60 + hpController.getHP() * 5, 50, MyData::GREEN, true);

	//for Debug
	DrawCircle(draw_x, draw_y, 5, MyData::GREEN, true);
	//DrawBox(draw_x, draw_y, draw_x + 32, draw_y + 64, BLACK, false);
	DrawFormatString(300, 140, BLACK, "p: %d %d", collision->p->raw_x, collision->p->raw_y);


}


//================================================
//内部protected関数
//================================================
void PlayerChild::standardAction(const Stage* _stage)
{
	onGround = isOnGround(_stage);
	onLadder = isOnLadder(_stage);

	actCheck();
	animeNum = animation();

	move(_stage);
	updateCamera();
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
		if (damagedTime < 3)hittedAction();
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
	if (Input_RIGHT())
	{
		dx += (int)(moveSpeed * MyData::vectorRate);
		direction = false;
	}
	if (Input_LEFT())
	{
		dx -= (int)(moveSpeed * MyData::vectorRate);
		direction = true;
	}

	//地上にいるなら
	if (jumpPower == 0 && onGround)
	{
		nowJumpCount = 0;
	}

	//はしごにのぼる
	if (onLadder)
	{
		if (Input_UP())
		{
			dy -= (int)(moveSpeed * MyData::vectorRate);
			jumpPower = 0.0f;
		}

		if (Input_DOWN())
		{
			dy += (int)(moveSpeed * MyData::vectorRate);
			jumpPower = 0.0f;
		}
	}

	//ジャンプ
	if (Input_JUMP() && !prePush && nowJumpCount < maxJumpCount)
	{
		jumpPower = maxJumpPower;
		nowJumpCount++;
	}

	//縦移動
	dy += gravity() * (actionState != ACT_LADDER) - jump();

	dx = getHorizontalDiffer(_stage, dx);
	dy = dy < 0 ? getTopDiffer(_stage, dy) : getBottomDiffer(_stage, dy);

	//天井に当たったら
	if (abs(dy) <= 1000)jumpPower = 0;

	//for Debug
	if (Input_UP()) dy = getTopDiffer(_stage, -3000);
	if (Input_DOWN())dy = getBottomDiffer(_stage, 3000);

	p->raw_x += dx;
	p->raw_y += dy;

	//マップ間移動
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

	prePush = Input_JUMP();
}

void PlayerChild::updateCamera()
{
	//for Debug
	//MyData::MAP_WIDTH * 2 の2はマップをつなげた個数

	//カメラ位置を更新
	int tmp_x = p->raw_x / MyData::vectorRate;
	int tmp_y = p->raw_y / MyData::vectorRate;

	if (tmp_x % MyData::MAP_WIDTH  <                     MyData::CX)tmp_x = MyData::MAP_WIDTH * (tmp_x / MyData::MAP_WIDTH) + MyData::CX;
	if (tmp_x % MyData::MAP_WIDTH  > MyData::MAP_WIDTH - MyData::CX)tmp_x = MyData::MAP_WIDTH * (tmp_x / MyData::MAP_WIDTH) + MyData::MAP_WIDTH - MyData::CX;

	if (tmp_y % MyData::MAP_HEIGHT <                      MyData::CY)tmp_y = MyData::MAP_HEIGHT * (tmp_y / MyData::MAP_HEIGHT) + MyData::CY;
	if (tmp_y % MyData::MAP_HEIGHT > MyData::MAP_HEIGHT - MyData::CY)tmp_y = MyData::MAP_HEIGHT * (tmp_y / MyData::MAP_HEIGHT) + MyData::MAP_HEIGHT - MyData::CY;


	*camera = Vector2(tmp_x, tmp_y);
}

bool PlayerChild::isOnGround(const Stage* _stage)
{
	//posはキャラの最下端よりひとつ下
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 + 1000);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate, true);


	//右上に向けた斜めブロックなら
	if (chipType == Stage::ChipType::TYPE_DOWN_SLANT_RIGHT)
	{
		pos.pos_y -= (MyData::CHIP_WIDTH_RATE() - p->pos_x() % MyData::CHIP_WIDTH_RATE());
		chipType = _stage->getChipType(pos / MyData::vectorRate, true);
	}

	//左上に向けた斜めブロックなら
	else if (chipType == Stage::ChipType::TYPE_DOWN_SLANT_LEFT)
	{
		pos.pos_y -= p->pos_x() % MyData::CHIP_WIDTH_RATE();
		chipType = _stage->getChipType(pos / MyData::vectorRate, true);
	}

	return !(chipType & (Stage::ChipType::TYPE_BACK | Stage::ChipType::TYPE_LADDER));
}

bool PlayerChild::isOnLadder(const Stage* _stage) const
{

	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 - 1);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate, true);

	return chipType == Stage::ChipType::TYPE_LADDER;
}

int PlayerChild::animation() 
{
	int num = 0 + direction;
	switch (actionState) 
	{
	case ACT_WALK:
		num = 8 + (animeCount / 10) % 4 + 8 * direction;
		break;
	case ACT_RUN:
		num = 12 + (animeCount / 10) % 4 + 8 * direction;
		break;
	case ACT_SIT:
		num = 24 + (animeCount >= 10);
		break;
	case ACT_ATTACK:
		num = 26 + direction;
		break;
	default:
		animeCount = 0;
		break;
	}

	animeCount++;

	assert(!(num < 0 || 40 <= num) && "自機画像範囲外");
	return num;
}

void PlayerChild::actCheck()
{
	if (onLadder)
	{
		if (Input_UP() || Input_DOWN())
		{
			actionState = ACT_LADDER;
		}

		if (Input_LEFT() || Input_RIGHT())
		{
			actionState = ((onGround) ? ACT_WALK : ACT_AIR);
		}

		if (onGround && !Input_UP())
		{
			actionState = ACT_NORMAL;
		}
	}
	else if (Input_ATTACK())actionState = ACT_ATTACK;
	else if (!onGround)actionState = ACT_AIR;
	else if (Input_DOWN())actionState = ACT_SIT;
	else if (Input_LEFT() || Input_RIGHT())actionState = ACT_WALK;
	else actionState = ACT_NORMAL;
}



}		
}
}