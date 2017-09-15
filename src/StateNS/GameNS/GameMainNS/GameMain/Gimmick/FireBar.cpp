#include "FireBar.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {


FireBar::FireBar(int _x, int _y) :
DynamicGimmickChild(_x, _y, 1.0)
{
	this->width  = 32;
	this->height = 32;

	x_1 = x_2 = _x;
	y_1 = _y - r_1;
	y_2 = _y - r_2;


	initialize();
}

FireBar::~FireBar()
{
	DeleteGraph(img_bar);
	DeleteGraph(img_fire);
}

void FireBar::initialize()
{
	this->radian = 0.0f;

	loadImage();
}

void FireBar::update(const Stage* _stage)
{
	radian += pi(1 / 180.0f);
	radian = fmod(radian, pi(2.0f));

	move();
	//standardMove(_stage);
}

void FireBar::draw(const Vector2* _camera) const
{
	standardDraw(_camera, p, scale, mImage, mDirection);

	//画面内にいなければreturn
	if (abs(p->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, mDirection);

	//for Debug
	draw_x = 320 + x_1 / vectorRate - _camera->x();
	draw_y = 240 + y_1 / vectorRate - _camera->y();
	DrawCircle(draw_x, draw_y, 5, RED);

	draw_x = 320 + x_2 / vectorRate - _camera->x();
	draw_y = 240 + y_2 / vectorRate - _camera->y();
	DrawCircle(draw_x, draw_y, 5, RED);

	//for Debug
	DrawFormatString(0, 70, BLACK, "F: %d, %d", p->x(), p->y());
}

void FireBar::apply(Character* _character)
{
	//character->damage();
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
	
	//for Debug;
	return false;
}

//==============================================
//内部プライベート関数
//==============================================
void FireBar::loadImage()
{
	this->mImage = LoadGraph("Data/Image/dossunn.png");
	assert(mImage != -1 && "FireBar画像読み込みエラー!");
}

void FireBar::move()
{
	float _cos = cosf(radian);
	x_1 = p->raw_x + (int)(r_1 * _cos);
	x_2 = p->raw_x + (int)(r_2 * _cos);

	float _sin = sinf(radian);
	y_1 = p->raw_y + (int)(r_1 * _sin);
	y_2 = p->raw_y + (int)(r_2 * _sin);
}




}
}
}