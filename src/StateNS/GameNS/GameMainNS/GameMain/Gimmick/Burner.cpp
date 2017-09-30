#include "Burner.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Burner::Burner(int _x, int _y,float _angle, bool _order) :
DynamicGimmickChild(_x, _y, 1.0)
{
	this->width  = 32;
	this->height = 32;

	this->r = _x + 4;
	this->l = _x - 4;
	this->d = _y + 4;
	this->u = _y - 4;

	this->angle = _angle;
	this->order = _order;

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


	int middle = (l_burn - l_block) / 2;
	int differ = middle + l_block;

	float _cos = cosf(this->angle);
	float _sin = sinf(this->angle);

	this->r += (int)(middle * _cos * _cos + differ * _cos);
	this->l += (int)(-middle * _cos * _cos + differ * _cos);
	this->d += (int)(middle * _sin * _sin + differ * _sin);
	this->u += (int)(-middle * _sin * _sin + differ * _sin);

	this->r *= vectorRate;
	this->l *= vectorRate;
	this->d *= vectorRate;
	this->u *= vectorRate;


	this->mTime = 0;
	this->isEmerge = false;
}

void Burner::update(const StageChild* _stage)
{
	mTime++;
	mTime %= 360;
	//if (0 + order * 180 <= mTime && mTime <= 180 + order * 180)isEmerge = true;
	//else isEmerge = false;

	isEmerge = (0 + order * 180 <= mTime && mTime <= 180 + order * 180);

	move();
}

void Burner::draw(const Vector2* _camera) const
{

	//画面内にいなければreturn
	if (abs(p->raw_x - _camera->raw_x) > 480000 || abs(p->raw_y - _camera->raw_y) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, img_block, true, mDirection);

	if (!isEmerge)return;
	DrawRotaGraph2(draw_x, draw_y, 16, 16, 1.0, angle, img_bar, true);


	//for Debug
	DrawBox(
		320 + l / 1000 - _camera->x(),
		240 + u / 1000 - _camera->y(),
		320 + r / 1000 - _camera->x(),
		240 + d / 1000 - _camera->y(),
		GREEN, false);
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

	return
		this->l < _player->raw_x + PLAYER_CHIP_WIDTH_RATE() / 3  &&
		this->r > _player->raw_x - PLAYER_CHIP_WIDTH_RATE() / 3 &&
		this->u < _player->raw_y + PLAYER_CHIP_HEIGHT_RATE() / 3 &&
		this->d > _player->raw_y - PLAYER_CHIP_HEIGHT_RATE() / 3;


	//枠の中なら return true じゃっかん広い？
	/*
	return
		distance(x_1, y_1, _player) < 16 * sqrt(2) * vectorRate ||
		distance(x_2, y_2, _player) < 16 * sqrt(2) * vectorRate ||
		distance(x_3, y_3, _player) < 16 * sqrt(2) * vectorRate;
	*/
}

//==============================================
//内部プライベート関数
//==============================================
void Burner::loadImage()
{
	//TODO バーナー用の画像に差し替え
	this->img_block = LoadGraph("Data/Image/fireblock.png");
	this->img_bar   = LoadGraph("Data/Image/firebar.png");
	assert((img_block != -1 || img_bar != -1)&& "Burner画像読み込みエラー!");
}

void Burner::move()
{
	
}




}
}
}