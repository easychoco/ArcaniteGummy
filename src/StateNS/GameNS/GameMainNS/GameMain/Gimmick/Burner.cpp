#include "Burner.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Burner::Burner(int _x, int _y,float _angle,bool _order) :
DynamicGimmickChild(_x, _y, 1.0)
{
	this->width  = 32;
	this->height = 32;

	x_1 = x_2 = x_3 = _x;
	y_1 = _y - r_1;
	y_2 = _y - r_2;
	y_3 = _y - r_3;
	this->angle = _angle;
	this->order = _order;
	this->mTime = 0;
	this->isEmerge = false;
	initialize();
}

Burner::~Burner()
{
	DeleteGraph(img_block);
	DeleteGraph(img_bar);
}

void Burner::initialize()
{



	loadImage();
}

void Burner::update(const StageChild* _stage)
{
	mTime++;
	mTime %= 360;
	if (0 + order * 180 <= mTime && mTime <= 180 + order * 180)isEmerge = true;
	else isEmerge = false;


	move();
}

void Burner::draw(const Vector2* _camera) const
{

	//画面内にいなければreturn
	if (abs(p->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, img_block, true, mDirection);

		//for Debug
	DrawFormatString(0, 70, BLACK, "BURN: %d, %d", p->x(), p->y());
	if (!isEmerge)return;
	DrawRotaGraph2(draw_x, draw_y, 16, 16, 1.0, angle, img_bar, true);


}

void Burner::apply(Character* _character)
{
	if(_character->isPlayer)_character->hpController.damage(this->damageValue);
}

void Burner::hittedAction()
{
	/* do nothing */
}

void Burner::burnedAction()
{
	/* do nothing */
}

bool Burner::isOverlap(const Vector2* _player) const
{
	return standardOverLap(_player);
}

bool Burner::onActiveArea(const Vector2* _player) const
{
	if (!isEmerge)return false;
	//枠の中なら return true じゃっかん広い？
	return
		distance(x_1, y_1, _player) < 16 * sqrt(2) * vectorRate ||
		distance(x_2, y_2, _player) < 16 * sqrt(2) * vectorRate ||
		distance(x_3, y_3, _player) < 16 * sqrt(2) * vectorRate;

	//半分しかできない↓
		/*
		p->x() + 32 * cosf(angle) - 16 * sinf(angle) <= _player->x() &&
		_player->x() <= p->x() + 128 * cosf(angle) + 16 * sinf(angle) &&
		p->y() + 32 * sinf(angle) - 16 * cosf(angle) <= _player->y() &&
		_player->y() <= p->y() + 128 * sinf(angle) + 16 * cosf(angle);
		*/
	//for Debug;
	return false;
}

//==============================================
//内部プライベート関数
//==============================================
void Burner::loadImage()
{
	this->img_block = LoadGraph("Data/Image/fireblock.png");
	this->img_bar   = LoadGraph("Data/Image/firebar.png");
	assert((img_block != -1 || img_bar != -1)&& "Burner画像読み込みエラー!");
}

void Burner::move()
{
	
	float _cos = cosf(angle);
	x_1 = p->raw_x + (int)(r_1 * _cos);
	x_2 = p->raw_x + (int)(r_2 * _cos);
	x_3 = p->raw_x + (int)(r_3 * _cos);

	float _sin = sinf(angle);
	y_1 = p->raw_y + (int)(r_1 * _sin);
	y_2 = p->raw_y + (int)(r_2 * _sin);
	y_3 = p->raw_y + (int)(r_3 * _sin);
	
}




}
}
}