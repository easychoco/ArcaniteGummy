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
	sound->deleteSound("tes");
}

void Config::initialize()
{
	this->volume = sound->allVolume;
	this->prePush = true;
	this->nowKeyConfig = false;
	this->configTime = 0;

	//for Debug
	sound->setSound("Data/Sound/Stage0.wav", "tes");
	sound->playSound("tes", BACK);
}

Child* Config::update(GrandParent* parent)
{
	Child* next = this;

	//音量調節画面
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
		//キーコンフィグ画面
		unsigned input = GetJoypadInputState(DX_INPUT_PAD1);
		if(input == 0)++configTime;
		else input = 0;

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
		DrawFormatString(0,  0, WHITE, "config Xで戻れるよ");
		DrawFormatString(0, 30, WHITE, "config Zでキーコンフィグ");


		DrawFormatString(20, 100, WHITE, "ボリューム調整");

		DrawBox(20, 130, 120, 150, WHITE, false);
		DrawBox(22, 132, (int)(22 + 96 * volume), 148, GREEN, true);

		//for Debug
		DrawFormatString(20, 160, WHITE, "%f", volume);
	}
	else
	{
		DrawFormatString(30,  30, DARKGLAY, "決定に使うボタンを押して");
		DrawFormatString(30,  60, DARKGLAY, "キャンセルに使うボタンを押して");
		DrawFormatString(30,  90, DARKGLAY, "攻撃に使うボタンを押して");
		DrawFormatString(30, 120, DARKGLAY, "ジャンプに使うボタンを押して");
		DrawFormatString(30, 150, DARKGLAY, "ダッシュに使うボタンを押して");
		DrawFormatString(30, 180, DARKGLAY, "特殊技に使うボタンを押して");
		DrawFormatString(30, 210, DARKGLAY, "キャラ交代に使うボタンを押して");
		DrawFormatString(30, 240, DARKGLAY, "ポーズに使うボタンを押して");
		DrawFormatString(30, 270, DARKGLAY, "上に使うボタンを押して");
		DrawFormatString(30, 300, DARKGLAY, "右に使うボタンを押して");
		DrawFormatString(30, 330, DARKGLAY, "下に使うボタンを押して");
		DrawFormatString(30, 360, DARKGLAY, "左に使うボタンを押して");

		switch (nowInput)
		{
		case  0: DrawFormatString(30,  30, WHITE, "決定に使うボタンを押して"); break;
		case  1: DrawFormatString(30,  60, WHITE, "キャンセルに使うボタンを押して"); break;
		case  2: DrawFormatString(30,  90, WHITE, "攻撃に使うボタンを押して"); break;
		case  3: DrawFormatString(30, 120, WHITE, "ジャンプに使うボタンを押して"); break;
		case  4: DrawFormatString(30, 150, WHITE, "ダッシュに使うボタンを押して"); break;
		case  5: DrawFormatString(30, 180, WHITE, "特殊技に使うボタンを押して"); break;
		case  6: DrawFormatString(30, 210, WHITE, "キャラ交代に使うボタンを押して"); break;
		case  7: DrawFormatString(30, 240, WHITE, "ポーズに使うボタンを押して"); break;
		case  8: DrawFormatString(30, 270, WHITE, "上に使うボタンを押して"); break;
		case  9: DrawFormatString(30, 300, WHITE, "右に使うボタンを押して"); break;
		case 10: DrawFormatString(30, 330, WHITE, "下に使うボタンを押して"); break;
		case 11: DrawFormatString(30, 360, WHITE, "左に使うボタンを押して"); break;
		}

		if (configTime > 30)
		{
			DrawBox(148, 148, 492, 202, WHITE, false);
			DrawBox(150, 150, 490, 200, BLACK, true);
			DrawString(170, 160, "ゲームパッドの入力がありません", WHITE);
		}
	}
}




}