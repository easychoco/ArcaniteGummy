#include "Guide.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

bool Guide::imgLoad = false;
int Guide::image;

Guide::Guide(int _x, int _y, vector<string> _messages ) :
GimmickChild(Vector2(_x, _y))
{
	this->messages = _messages;
	initialize();
}

Guide::~Guide()
{
	messages.clear();
	messages.shrink_to_fit();
}

void Guide::initialize()
{
	loadImage();

	this->mTime = 0;
	this->activeWhenStopping = true;


	int max_str_num = 0;
	for (const auto& m : messages)
	{
		max_str_num = max(max_str_num, (int)m.size());
	}
	frameWidth = max_str_num * 15;
	frameHeight = messages.size() * 30;
}

void Guide::update()
{
	if (this->playerLooking)
	{
		mTime = min(mTime + 1, 30);
	}
	else
	{
		mTime = 0;
	}

	this->playerLooking = false;
}

void Guide::draw(const Vector2* _camera) const
{
	//画面内にいなければreturn
	if (abs(pos.raw_x - _camera->raw_x) > 480000 || abs(pos.raw_y - _camera->raw_y) > 320000)return;

	int draw_x = MyData::CX + pos.x() - _camera->x();
	int draw_y = MyData::CY + pos.y() - _camera->y();

	//描画
	DrawRotaGraph(draw_x, draw_y - 16, 1.0, 0.0, image, true, false);

	//プレイヤーが近くにいたら内容を表示
	if (playerLooking)
	{
		DrawFilledCircledBox(draw_x + 10, draw_y - 10 - frameHeight, draw_x + frameWidth, draw_y - 10, 15, BLACK);
		for (unsigned i = 0; i < messages.size(); i++)
		{
			DrawString(draw_x + 20, draw_y - frameHeight + i * 30, messages[i].c_str(), WHITE);
		}
	}
}

void Guide::apply(Character* _character)
{
	this->playerLooking = true;
}

bool Guide::onActiveArea(const Vector2* _player) const
{
	//他のギミックよりも範囲を広めにする
	int half_w = 64000;
	int half_h = 32000;

	return
		this->pos.raw_x - half_w <= _player->raw_x &&
		this->pos.raw_x + half_w >= _player->raw_x &&
		this->pos.raw_y - half_h <= _player->raw_y &&
		this->pos.raw_y + half_h >= _player->raw_y;
}

//==============================================
//内部プライベート関数
//==============================================
void Guide::loadImage()
{
	if (!imgLoad)
	{
		this->image = LoadGraph("Data/Image/Guide.png");
		assert((image != -1) && "Guide画像読み込みエラー!");
	}
	imgLoad = true;
}



}
}
}