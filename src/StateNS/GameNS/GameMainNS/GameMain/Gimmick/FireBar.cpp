#include "FireBar.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

bool FireBar::imgLoad = false;
int FireBar::img_block;
int FireBar::img_bar;


FireBar::FireBar(int _x, int _y,bool _ways) :
DynamicGimmickChild(_x, _y, 1.0)
{
	this->width  = 32;
	this->height = 32;

	x_1 = x_2 = x_3 = _x;
	y_1 = _y - r_1;
	y_2 = _y - r_2;
	y_3 = _y - r_3;
	ways = _ways;
	initialize();
}

FireBar::~FireBar()
{
	//DeleteGraphはしない
}

void FireBar::initialize()
{
	this->radian = 0.0f;

	loadImage();
}

void FireBar::update(const StageChild* _stage)
{
	radian += ways ? pi(1 / 180.0f) : -pi(1 / 180.0f);
	radian = fmod(radian, pi(2.0f));

	move();
}

void FireBar::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(p->raw_x - _camera->raw_x) > 480000 || abs(p->raw_y - _camera->raw_y) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, img_block, true, mDirection);
	DrawRotaGraph2(draw_x, draw_y, 16, 16, 1.0, radian, img_bar, true);

}

void FireBar::apply(Character* _character)
{
	if(_character->isPlayer)_character->hpController.damage(this->damageValue);
}

void FireBar::hittedAction()
{
	/* do nothing */
}

void FireBar::burnedAction()
{
	/* do nothing */
}

bool FireBar::isOverlap(const Vector2* _player) const
{
	return standardOverLap(_player);
}

bool FireBar::onActiveArea(const Vector2* _player) const
{
	//二つの点との距離が16未満なら return true
	return
		distance(x_1, y_1, _player) < 16 * vectorRate ||
		distance(x_2, y_2, _player) < 16 * vectorRate ||
		distance(x_3, y_3, _player) < 16 * vectorRate;
}

//==============================================
//内部プライベート関数
//==============================================
void FireBar::loadImage()
{
	if (!imgLoad)
	{
		this->img_block = LoadGraph("Data/Image/fireblock.png");
		this->img_bar = LoadGraph("Data/Image/firebar.png");
		assert((img_block != -1 || img_bar != -1) && "FireBar画像読み込みエラー!");
	}
	imgLoad = true;
}

void FireBar::move()
{
	float _cos = cosf(radian);
	x_1 = p->raw_x + (int)(r_1 * _cos);
	x_2 = p->raw_x + (int)(r_2 * _cos);
	x_3 = p->raw_x + (int)(r_3 * _cos);

	float _sin = sinf(radian);
	y_1 = p->raw_y + (int)(r_1 * _sin);
	y_2 = p->raw_y + (int)(r_2 * _sin);
	y_3 = p->raw_y + (int)(r_3 * _sin);
}




}
}
}