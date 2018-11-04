#include "Stage11.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"
#include "..\Gimmick\Guide.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage11::Stage11() :
StageChild(2, 1) //�G���A�̐�: �悱�C����
{
	initialize();
}

Stage11::~Stage11()
{
	sound->deleteSound("bgm1");
}

void Stage11::initialize()
{
	//�_�̃G�t�F�N�g�����ɗ����悤�ɂ���
	this->drawEffect = true;
	this->backDrawType = DRAW_HORIZONTAL;
	this->setEffectImage("Data/Image/effect_cloud.png");

	this->setBackImage("Data/Image/back1.jpg");

	sound->setSound("Data/Sound/stage1.wav", "bgm1");
	sound->playSound("bgm1", LOOP, false);

	//�ύX�ł���L�����N�^�[��ݒ�
	this->changeableCharacter |= CHARA_MOKOU;
	//���ォ��E��push���Ă���
	//StageID, 0���珸��, �G���A�̌`
	this->maps.push_back(new Map(11, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(11, 1, MapPos::POS_LEFT_FREE));

	vector<string> message
	{
		"���g�̃T�|�[�g��",
		"���A�㔒��d����",
		"�C���Ă���",
		"������Ȃ����Ƃ���������",
		"���ĊŔ����Ă���",
	};

	Guide* guide = new Guide(272, 1552, message);
	maps[0]->addGimmick(guide);

	vector<string> message2
	{
		"�S�[���t���O��",
		"���������",
		"�X�e�[�W�N���A����",
	};

	Guide* guide2 = new Guide(89*32+16, 39*32+16, message2);
	maps[1]->addGimmick(guide2);

	vector<string> message3
	{
		"���ōU������",
		"�G��|����",
		"�c�O�Ȃ���",
		"���݂��邱�Ƃ͂ł��Ȃ�",
	};

	Guide* guide3 = new Guide(18 * 32 + 16, 47 * 32 + 16, message3);
	maps[0]->addGimmick(guide3);

	vector<string> message4
	{
		"���g�͓�i�W�����v��",
		"�ł��邩��",
		"��������ɓ͂���"
	};

	Guide* guide4 = new Guide(31 * 32 + 16, 48 * 32 + 16, message4);
	maps[0]->addGimmick(guide4);

	vector<string> message5
	{
		"�_�b�V������",
		"��C�ɋ삯�����邱�Ƃ��ł��邼"
	};

	Guide* guide5 = new Guide(47 * 32 + 16, 48 * 32 + 16, message5);
	maps[0]->addGimmick(guide5);

	vector<string> message6
	{
		"�����Ȏ�ނ̓G�����邩��",
		"���ӂ��K�v����"
	};

	Guide* guide6 = new Guide(8 * 32 + 16, 45 * 32 + 16, message6);
	maps[1]->addGimmick(guide6);



	flag = new ClearFlag(Vector2(3056, 1264));
	maps[1]->addGimmick(flag);
	
	startX = 144, startY = 1536;
	converseFlag0 = true;

	//����
	bool restart = findRestartPoint();
	//�����������b�t���O��܂�
	if (restart)
	{
		converseFlag0 = false;
	}
}


void Stage11::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain, _player);
	standardUpdate(_player);
}

void Stage11::updateConverse(GameMain* gameMain, PlayerChild* _player)
{
	if (converseFlag0)
	{
		gameMain->startConverse(110);
		converseFlag0 = false;
	}
}

void Stage11::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage11::isClear() const
{
	return !flag->isActive;
}


}
}
}


