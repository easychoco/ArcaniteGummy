#include "Config.h"
#include "StateParent.h"

#include "..\Data.h"
#include "..\KeyInput.h"
#include "Title.h"

#include <fstream>


namespace StateNS{



Config::Config()
{
	initialize();
}

Config::~Config()
{
	sound->allVolume = volume;
	sound->deleteSound("bgm");
}

void Config::initialize()
{
	this->volume = sound->allVolume;
	this->prePush = true;
	this->nowKeyConfig = false;
	this->configTime = 0;
	this->padResponse = false;

	sound->setSound("Data/Sound/OP.wav", "bgm");
	sound->playSound("bgm", BACK);
}

Child* Config::update(GrandParent* parent)
{
	Child* next = this;

	//���ʒ��߉��
	if (!nowKeyConfig)
	{
		if (Input_NO())next = new StateNS::Title(2, 2);

		if (!prePush && Input_OK())
		{
			nowKeyConfig = true;
			prePush = true;
			nowInput = 0;
			configTime = 0;
		}
		if (backFromConfig && !Input_LEFT() && !Input_RIGHT())backFromConfig = false;
		bool changed = false;
		if (Input_LEFT() && !backFromConfig)
		{
			volume = max(volume - 0.05f, 0.0f);
			changed = true;
		}
		if (Input_RIGHT() && !backFromConfig)
		{
			volume = min(volume + 0.05f, 1.0f);
			changed = true;
		}

		if (changed)MyData::sound->setAllVolume(volume);

		prePush = Input_OK();
	}
	else
	{
		//�L�[�R���t�B�O���
		unsigned input = GetJoypadInputState(DX_INPUT_PAD1);
		if(input == 0 && !padResponse)++configTime;
		else
		{
			configTime = 0;
			padResponse = true;
		}

		if (!prePush && input > 0)
		{
			switch (nowInput)
			{
			case  0: setOK(input); break;
			case  1: setNO(input); break;
			case  2: setATTACK(input); break;
			case  3: setJUMP(input); break;
			case  4: setDASH(input); break;
			case  5: setSPECIAL(input); break;
			case  6: setCHANGE(input); break;
			case  7: setPAUSE(input); break;
			case  8: setUP(input); break;
			case  9: setRIGHT(input); break;
			case 10: setDOWN(input); break;
			case 11: setLEFT(input); break;
			}
			++nowInput;

		}
		prePush = (input > 0);
		if (nowInput > 11 || configTime > 120)
		{
			nowKeyConfig = false;
			backFromConfig = true;
			saveKeyConfig();
		}
	}

	return next;
}

void Config::draw() const
{
	if (!nowKeyConfig)
	{
		DrawFormatString(0,  0, WHITE, "�����Ă�");
		DrawFormatString(0, 30, WHITE, "Z�L�[�ŃL�[�R���t�B�O�J�n�@X�L�[�Ŗ߂�");

		DrawFormatString(20, 100, WHITE, "���E�L�[�Ń{�����[������");

		DrawBox(20, 130, 120, 150, WHITE, false);
		DrawBox(22, 132, (int)(22 + 96 * volume), 148, GREEN, true);

		DrawFormatString(20, 160, WHITE, "%f", volume);
	}
	else
	{
		DrawFormatString(30,  30, DARKGLAY, "����Ɏg���{�^����������");
		DrawFormatString(30,  60, DARKGLAY, "�L�����Z���Ɏg���{�^����������");
		DrawFormatString(30,  90, DARKGLAY, "�U���Ɏg���{�^����������");
		DrawFormatString(30, 120, DARKGLAY, "�W�����v�Ɏg���{�^����������");
		DrawFormatString(30, 150, DARKGLAY, "�_�b�V���Ɏg���{�^����������");
		DrawFormatString(30, 180, DARKGLAY, "����Z�Ɏg���{�^����������");
		DrawFormatString(30, 210, DARKGLAY, "�L�������Ɏg���{�^����������");
		DrawFormatString(30, 240, DARKGLAY, "�|�[�Y�Ɏg���{�^����������");
		DrawFormatString(30, 270, DARKGLAY, "��Ɏg���{�^����������");
		DrawFormatString(30, 300, DARKGLAY, "�E�Ɏg���{�^����������");
		DrawFormatString(30, 330, DARKGLAY, "���Ɏg���{�^����������");
		DrawFormatString(30, 360, DARKGLAY, "���Ɏg���{�^����������");

		switch (nowInput)
		{
		case  0: DrawFormatString(30,  30, WHITE, "����Ɏg���{�^����������"); break;
		case  1: DrawFormatString(30,  60, WHITE, "�L�����Z���Ɏg���{�^����������"); break;
		case  2: DrawFormatString(30,  90, WHITE, "�U���Ɏg���{�^����������"); break;
		case  3: DrawFormatString(30, 120, WHITE, "�W�����v�Ɏg���{�^����������"); break;
		case  4: DrawFormatString(30, 150, WHITE, "�_�b�V���Ɏg���{�^����������"); break;
		case  5: DrawFormatString(30, 180, WHITE, "����Z�Ɏg���{�^����������"); break;
		case  6: DrawFormatString(30, 210, WHITE, "�L�������Ɏg���{�^����������"); break;
		case  7: DrawFormatString(30, 240, WHITE, "�|�[�Y�Ɏg���{�^����������"); break;
		case  8: DrawFormatString(30, 270, WHITE, "��Ɏg���{�^����������"); break;
		case  9: DrawFormatString(30, 300, WHITE, "�E�Ɏg���{�^����������"); break;
		case 10: DrawFormatString(30, 330, WHITE, "���Ɏg���{�^����������"); break;
		case 11: DrawFormatString(30, 360, WHITE, "���Ɏg���{�^����������"); break;
		}

		if (configTime > 30)
		{
			DrawBox(148, 148, 492, 202, WHITE, false);
			DrawBox(150, 150, 490, 200, BLACK, true);
			DrawString(170, 160, "�Q�[���p�b�h�̓��͂�����܂���", WHITE);
		}
	}
}




}