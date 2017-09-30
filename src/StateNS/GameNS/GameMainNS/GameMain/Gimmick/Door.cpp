#include "Door.h"
#include "..\Character.h"
#include "..\..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Door::Door(Vector2* _pos1, Vector2* _pos2) : 
GimmickChild(*_pos1)
{
	this->door1 = _pos1;
	this->door2 = _pos2;

	initialize();
}

Door::~Door()
{
	SAFE_DELETE(door1);
	SAFE_DELETE(door2);
}

void Door::initialize()
{
	loadImage();
	
	onDoor1 = false;
	onDoor2 = false;
}

void Door::update()
{
	animeTime = max(0, animeTime - 1);
}

void Door::draw(const Vector2* _camera) const
{

	//Door1
	int draw_x = 320 + (door1->raw_x - _camera->raw_x) / MyData::vectorRate;
	int draw_y = 240 + (door1->raw_y - _camera->raw_y) / MyData::vectorRate;

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true);

	//Door2
	draw_x = 320 + (door2->raw_x - _camera->raw_x) / MyData::vectorRate;
	draw_y = 240 + (door2->raw_y - _camera->raw_y) / MyData::vectorRate;

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true);
}

void Door::draw_front(const Vector2* _camera) const
{
	//アニメーション途中なら
	if (animeTime > 0)
	{
		int rx = animeTime * 8;
		int ry = animeTime * 6;
		DrawBox(320 - rx, 240 - ry, 320 + rx, 240 + ry, BLACK, true);
	}
}

void Door::apply(Character* _character)
{
	if (animeTime > 0)return;

	onDoor1 = abs(door1->raw_x - _character->getVector2()->raw_x) < PLAYER_CHIP_WIDTH_RATE() && abs(door1->raw_y - _character->getVector2()->raw_y) < PLAYER_CHIP_HEIGHT_RATE();
	onDoor2 = abs(door2->raw_x - _character->getVector2()->raw_x) < PLAYER_CHIP_WIDTH_RATE() && abs(door2->raw_y - _character->getVector2()->raw_y) < PLAYER_CHIP_HEIGHT_RATE();

	if (onDoor1)_character->warpCharacter(door2->raw_x, door2->raw_y);
	if (onDoor2)_character->warpCharacter(door1->raw_x, door1->raw_y);
	if (onDoor1 || onDoor2)
	{
		onDoor1 = !onDoor1;
		onDoor2 = !onDoor2;
		animeTime = 40;
	}
}

bool Door::isOverlap(int _sub_x, int _sub_y) const
{
	return
		this->pos.x() / MyData::CHIP_WIDTH  == _sub_x &&
		this->pos.y() / MyData::CHIP_HEIGHT == _sub_y;
}

bool Door::onActiveArea(const Vector2* _player) const
{
	return Input_UP();
}

//==============================================
//内部プライベート関数
//==============================================
void Door::loadImage()
{
	mImage = LoadGraph("Data/Image/Door.png");
	assert(mImage != -1 && "ドア画像読み込みエラー！");
}


}
}
}