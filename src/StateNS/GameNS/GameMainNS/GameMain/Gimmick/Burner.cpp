#include "Burner.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

bool Burner::imgLoad;
int Burner::img_block;
int Burner::img_bars[3];

Burner::Burner(int _x, int _y, float _angle, bool _order) :
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

	loadImage();

	initialize();
}

Burner::~Burner()
{
	//DeleteGraphはしない
}

void Burner::initialize()
{
	int middle = (l_burn - l_block) / 2;
	int differ = (l_burn + l_block) / 2;

	float _cos = cosf(this->angle);
	float _sin = sinf(this->angle);
	
	this->r += (int)( middle * _cos * _cos + differ * _cos);
	this->l += (int)(-middle * _cos * _cos + differ * _cos);
	this->d += (int)( middle * _sin * _sin + differ * _sin);
	this->u += (int)(-middle * _sin * _sin + differ * _sin);

	this->r *= vectorRate;
	this->l *= vectorRate;
	this->d *= vectorRate;
	this->u *= vectorRate;


	this->mTime = 0;
	this->isEmerge = false;
	this->drawBurner = true;
}

void Burner::update(const StageChild* _stage)
{
	mTime++;
	mTime %= 360;

	isEmerge = false;
	drawBurner = true;
	
		 if (     order * 180 <= mTime && mTime <  20 + order * 180)img_bar = img_bars[0];
	else if (20 + order * 180 <= mTime && mTime <  40 + order * 180)img_bar = img_bars[1];
	else if (40 + order * 180 <= mTime && mTime < 150 + order * 180)
	{
		img_bar = img_bars[2];
		isEmerge = true;
	}
	else
	{
		drawBurner = false;
	}

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

	if(drawBurner)DrawRotaGraph2(draw_x, draw_y, -16, 16, 1.0, angle, img_bar, true);
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
}

//==============================================
//内部プライベート関数
//==============================================
void Burner::loadImage()
{
	if (!imgLoad)
	{
		this->img_block = LoadGraph("Data/Image/fireblock.png");
		int tmp = LoadDivGraph("Data/Image/fire.png", 3, 1, 3, 96, 32, img_bars);
		assert((img_block != -1 || tmp != -1) && "Burner画像読み込みエラー!");
	}
	imgLoad = true;
}

void Burner::move()
{
	
}




}
}
}