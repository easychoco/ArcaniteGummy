#include "PlayerChild.h"

#include "..\Stage.h"

//for Debug
#include "..\Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


PlayerChild::PlayerChild(int _x, int _y, float _move,float _jump,int _jumpCount, int _hp) : 
Character(_hp, _x, _y, MyData::PLAYER_CHIP_WIDTH, MyData::PLAYER_CHIP_HEIGHT,_jump,_jumpCount),
maxMoveSpeed(_move)
{
	initialize();
	assert(mImage != -1 && "自機画像読み込みエラー");
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

	post_x = MyData::MAP_WIDTH / 2;
	post_y = MyData::MAP_HEIGHT / 2;
}

void PlayerChild::draw() const
{	
	int draw_x = MyData::CX + (p->pos_x() - camera->pos_x()) / MyData::vectorRate;
	int draw_y = MyData::CY + (p->pos_y() - camera->pos_y()) / MyData::vectorRate;

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, direction);
	DrawCircle(draw_x, draw_y, 5, MyData::GREEN, true);

	draw_other();
	draw_changingAnimation(draw_x, draw_y);

	//for Debug
	DrawBox(60, 20, 60 + hpController.getHP() * 5, 50, MyData::GREEN, true);
	DrawFormatString(0, 50, MyData::BLACK, "player : %d %d", p->pos_x(), p->pos_y());
	DrawFormatString(0, 70, MyData::BLACK, "colli  : %d %d", collision->p->x(), collision->p->y());
	DrawFormatString(0, 90, MyData::BLACK, "camera : %d %d", camera->x(), camera->y());
}


//================================================
//内部protected関数
//================================================
void PlayerChild::standardAction(const Stage* _stage)
{
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
	
	prePush = Input_JUMP();
}

void PlayerChild::updateCamera()
{
	//for Debug
	//MyData::MAP_WIDTH * 2 の2はマップをつなげた個数

	//カメラ位置を更新
	//int tmp_x = max(MyData::CX, min(MyData::MAP_WIDTH  * 2 - MyData::CX, p->raw_x / MyData::vectorRate));
	//int tmp_y = max(MyData::CY, min(MyData::MAP_HEIGHT * 2 - MyData::CY, p->raw_y / MyData::vectorRate));

	int tmp_x = p->raw_x / MyData::vectorRate;
	int tmp_y = p->raw_y / MyData::vectorRate;

	if(tmp_x % 960 < 320)tmp_x = 960 * (tmp_x / 960) + 320;
	if (tmp_x % 960 > 640)tmp_x = 960 * (tmp_x / 960) + 640;

	if (tmp_y % 640 < 240)tmp_y = 640 * (tmp_y / 640) + 240;
	if (tmp_y % 640 > 400)tmp_y = 640 * (tmp_y / 640) + 400;

	*camera = Vector2(tmp_x, tmp_y);
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

}
}
}