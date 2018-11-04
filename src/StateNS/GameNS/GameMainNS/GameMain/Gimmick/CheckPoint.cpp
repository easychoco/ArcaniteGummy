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
	sound->deleteSound("checkpoint");
}

void CheckPoint::initialize()
{
	this->time = 120;
	visited = false;
	loadImage();
	sound->setSound("Data/Sound/checkpoint.mp3", "checkpoint");
}

void CheckPoint::update()
{
	++time;
	visited = false;
}

void CheckPoint::draw(const Vector2* _camera) const
{
	//��ʓ��ɂ��Ȃ����return
	if (abs(pos.raw_x - _camera->raw_x) > 340000 || abs(pos.raw_y - _camera->raw_y) > 260000)return;

	int draw_x = MyData::CX + pos.x() - _camera->x();
	int draw_y = MyData::CY + pos.y() - _camera->y();

	//�`��
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, image, true, false);

	//������摜�̒��S���΂ɂȂ�
	if (time < 60) DrawCircle(draw_x, draw_y - 3, 8, CYAN, true);
	else DrawCircle(draw_x, draw_y - 3, 8, RED, true);
}

void CheckPoint::apply(Character* _character)
{
	//��x����ƁC2�b�Ԗ���
	if (time < 60)return;

	//��
	_character->hpController.recover(PLAYER_MAX_HP);

	sound->playSound("checkpoint");

	visited = true;
	time = 0;
}

bool CheckPoint::onActiveArea(const Vector2* _player) const
{
	return isOverlap(_player);
}

//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void CheckPoint::loadImage()
{
	if (!imgLoad)
	{
		this->image = LoadGraph("Data/Image/CheckPoint.png");
		assert((image != -1) && "CheckPoint�摜�ǂݍ��݃G���[!");
	}
	imgLoad = true;
}



}
}
}