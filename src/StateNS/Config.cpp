#include "Config.h"
#include "StateParent.h"

#include "..\Data.h"
#include "..\KeyInput.h"
#include "Title.h"


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

	//for Debug
	sound->setSound("Data/Sound/Stage0.wav", "tes");
	sound->playSound("tes", BACK);
}

Child* Config::update(const GrandParent* parent)
{
	Child* next = this;
	if (Input_X())next = new StateNS::Title(2, 2);

	bool changed = false;
	if (Input_LEFT())
	{
		volume = max(volume - 0.05f, 0.0f);
		changed = true;
	}
	if (Input_RIGHT())
	{
		volume = min(volume + 0.05f, 1.0f);
		changed = true;
	}

	if(changed)MyData::sound->setAllVolume(volume);

	return next;
}

void Config::draw() const
{
	DrawFormatString(0, 0, WHITE, "config XÇ≈ñﬂÇÍÇÈÇÊ");


	DrawFormatString(20, 100, WHITE, "É{ÉäÉÖÅ[ÉÄí≤êÆ");

	DrawBox(20, 130, 120, 150, WHITE, false);
	DrawBox(22, 132, (int)(22 + 96 * volume), 148, GREEN, true);

	//for Debug
	DrawFormatString(20, 160, WHITE, "%f", volume);

}




}