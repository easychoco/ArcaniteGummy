#include "Clear.h"
#include "..\StateParent.h"

#include "Play.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {

Clear::Clear()
{
	initialize();
}


Clear::~Clear()
{
	sound->stopSoundOfFile();

}

void Clear::initialize()
{
	saved = false;
	sound->playSoundWithPath("Data/Sound/clear.mp3", BACK);
}

Child* Clear::update(StateNS::Parent* _parent)
{
	if (!saved)
	{
		int nextStage = _parent->stageNum;

		//クリアしたら
		if (nextStage == 53)nextStage = 11;
		else if (nextStage % 10 == 3)nextStage += 8;
		else ++nextStage;

		saveData->save(nextStage);
		saveData->resetCheckPoint();
		saved = true;
	}

	Child* next = this;

	if (Input_C())
	{
		_parent->moveTo(_parent->NextSequence::SEQ_TITLE);
	}

	//次のステージへ
	if (Input_Z())
	{
		int nextStage = _parent->stageNum;
	
		//クリアしたら
		if (nextStage == 53)nextStage = 11;
		else if (nextStage % 10 == 3)nextStage += 8;
		else ++nextStage;

		_parent->stageNum = nextStage;
		next = new Play(nextStage);
	}

	return next;
}

void Clear::draw() const
{
	DrawFormatString(250, 220, MyData::WHITE, "くりあー！");
	DrawFormatString(250, 320, MyData::WHITE, "Zで次へ");
	DrawFormatString(250, 350, MyData::WHITE, "Cでタイトルへ");
}






}
}

