#include "MusicRoom.h"
#include "StateParent.h"
#include "..\Data.h"
#include "..\KeyInput.h"
#include "Title.h"


namespace StateNS{



MusicRoom::MusicRoom()
{
	initialize();
}

MusicRoom::~MusicRoom()
{
	sound->deleteSound("titlebgm2");
	sound->deleteSound("boss1");
	sound->deleteSound("boss2");
	sound->deleteSound("boss3");
	sound->deleteSound("boss4");
	sound->deleteSound("boss5");
	sound->deleteSound("bgm2");
	sound->deleteSound("bgm3");
	sound->deleteSound("bgm4");
	DeleteGraph(*images);
}

void MusicRoom::initialize()
{
	sound->stopAllSound();
	sound->setSound("Data/Sound/OP.wav", "titlebgm2");
	sound->setSound("Data/Sound/Invisible_Full_Moon.wav", "boss1");
	sound->setSound("Data/Sound/Ousa-sama3.wav", "bgm2");
	sound->setSound("Data/Sound/Pure_Furies.wav", "boss2");
	sound->setSound("Data/Sound/Phantom_Ship.wav", "bgm3");
	sound->setSound("Data/Sound/husi.wav", "boss3");
	sound->setSound("Data/Sound/hyakunen.wav", "bgm4");
	sound->setSound("Data/Sound/uno-en.wav", "boss4");
	sound->setSound("Data/Sound/taketori.wav", "boss5");


	LoadDivGraph("Data/Image/chip_mokou.png", 32, 8, 4, 32, 64, images, TRUE);
	assert(*images != -1 && "���@�摜�ǂݍ��݃G���[");
	time = 0;

	dx = 0;
	draw_x = 50;
	direction = false;
	animeNum = 0;
	prePushUP = true;
	prePushDOWN = true;
	prePushOK = true;
	nowSelect = 0;

}

Child* MusicRoom::update(GrandParent* parent)
{
	Child* next = this;
	if (Input_NO())next = new StateNS::Title(2,1);


	if (Input_UP() && !prePushUP)nowSelect = (nowSelect + 8) % 9;
	else if (Input_DOWN() && !prePushDOWN)nowSelect = (nowSelect + 1) % 9;


	if (Input_OK() && !prePushOK) 
	{
		sound->stopAllSound();
		switch (nowSelect) 
		{
		case 0:sound->playSound("titlebgm2"); break;
		case 1:sound->playSound("boss1"); break;
		case 2:sound->playSound("bgm2"); break;
		case 3:sound->playSound("boss2"); break;
		case 4:sound->playSound("bgm3"); break;
		case 5:sound->playSound("boss3"); break;
		case 6:sound->playSound("bgm4"); break;
		case 7:sound->playSound("boss4"); break;
		case 8:sound->playSound("boss5"); break;
		}
	
	}


	charmove();
	time++;

	prePushUP = Input_UP();
	prePushDOWN = Input_DOWN();
	prePushOK = Input_OK();

	return next;
}

void MusicRoom::charmove()
{
	animeNum=8 + (time / 10) % 4;
	if (Input_LEFT())direction = true;
	else if (Input_RIGHT())direction = false;
	else {
		animeNum = 0;
		return;
	}
	int temp_x = direction ? -2 : 2;
	draw_x = max(draw_x + temp_x, 16);
	draw_x = min(draw_x + temp_x, 624);

}


void MusicRoom::draw() const
{
	DrawFormatString(0, 0, WHITE, "�݂�[��������[�ށ@�L�����Z���{�^���Ŗ߂�");
	DrawFormatString(30, 30, DARKGLAY, "�^�C�g�����");
	DrawFormatString(30, 60, DARKGLAY, "�X�e�[�W1�{�X�F���C�̓��@�` Invisible Full Moon");
	DrawFormatString(30, 90, DARKGLAY, "�X�e�[�W2�����F���F�����܂̑f����");
	DrawFormatString(30, 120, DARKGLAY, "�X�e�[�W2�{�X�F�s���A�q���[���[�Y�@�` �S�̍ݏ�");
	DrawFormatString(30, 150, DARKGLAY, "�X�e�[�W3�����F�H��q�D�Ǝ���𒴂�����");
	DrawFormatString(30, 180, DARKGLAY, "�X�e�[�W3�{�X�F���܂œ͂��A�s���̉�");
	DrawFormatString(30, 210, DARKGLAY, "�X�e�[�W4�����F���@�����B�̕S�N��");
	DrawFormatString(30, 240, DARKGLAY, "�X�e�[�W4�{�X�FU.N.�I�[�G���͔ޏ��Ȃ̂��H");
	DrawFormatString(30, 270, DARKGLAY, "�X�e�[�W5�{�X�F�|����ā@�` Lunatic Princess");


	switch (nowSelect)
	{
	case  0: DrawFormatString(30, 30, WHITE, "�^�C�g�����"); break;
	case  1: DrawFormatString(30, 60, WHITE, "�X�e�[�W1�{�X�F���C�̓��@�` Invisible Full Moon"); break;
	case  2: DrawFormatString(30, 90, WHITE, "�X�e�[�W2�����F���F�����܂̑f����"); break;
	case  3: DrawFormatString(30, 120, WHITE, "�X�e�[�W2�{�X�F�s���A�q���[���[�Y�@�` �S�̍ݏ�"); break;
	case  4: DrawFormatString(30, 150, WHITE, "�X�e�[�W3�����F�H��q�D�Ǝ���𒴂�����"); break;
	case  5: DrawFormatString(30, 180, WHITE, "�X�e�[�W3�{�X�F���܂œ͂��A�s���̉�"); break;
	case  6: DrawFormatString(30, 210, WHITE, "�X�e�[�W4�����F���@�����B�̕S�N��"); break;
	case  7: DrawFormatString(30, 240, WHITE, "�X�e�[�W4�{�X�FU.N.�I�[�G���͔ޏ��Ȃ̂��H"); break;
	case  8: DrawFormatString(30, 270, WHITE, "�X�e�[�W5�{�X�F�|����ā@�` Lunatic Princess"); break;
	}

	DrawRotaGraph(draw_x, 350, 1.0, 0.0, images[animeNum], true, direction);

}




}