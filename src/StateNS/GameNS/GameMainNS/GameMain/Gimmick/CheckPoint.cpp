#include "CheckPoint.h"
#include "..\Player\PlayerChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

	
bool CheckPoint::imgLoad = false;
int CheckPoint::image;

CheckPoint::CheckPoint(int _x, int _y, int _stage_num):
GimmickChild(Vector2(_x, _y)),
stage_num(_stage_num)
{
	initialize();
}

CheckPoint::~CheckPoint()
{

}

void CheckPoint::initialize()
{
	this->time = 60;
	visited = false;
	loadImage();
}

void CheckPoint::update()
{
	++time;
	visited = false;
}

void CheckPoint::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(pos.raw_x - _camera->raw_x) > 340000 || abs(pos.raw_y - _camera->raw_y) > 260000)return;

	int draw_x = MyData::CX + pos.x() - _camera->x();
	int draw_y = MyData::CY + pos.y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, image, true, false);

	//来たら画像の中心が緑になる
	if (time < 120) DrawCircle(draw_x, draw_y - 3, 8, CYAN, true);
	else DrawCircle(draw_x, draw_y - 3, 8, RED, true);
}

void CheckPoint::apply(Character* _character)
{
	//一度来ると，1秒間無効
	if (time < 60)return;


	//TODO 音鳴らすとか

	visited = true;
	time = 0;
}

bool CheckPoint::onActiveArea(const Vector2* _player) const
{
	return isOverlap(_player);
}

//==============================================
//内部プライベート関数
//==============================================
void CheckPoint::loadImage()
{
	if (!imgLoad)
	{
		this->image = LoadGraph("Data/Image/CheckPoint.png");
		assert((image != -1) && "CheckPoint画像読み込みエラー!");
	}
	imgLoad = true;
}



}
}
}