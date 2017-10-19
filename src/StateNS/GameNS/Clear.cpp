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
	prePushZ = true;
	prePushUD = true;
	cursorPos = 0;
	sound->playSoundWithPath("Data/Sound/clear.mp3", BACK);
	LoadDivGraph("Data/Image/Character/chip_mokou.png", 32, 8, 4, 32, 64, images, TRUE);
	assert(*images != -1 && "自機画像読み込みエラー");
	backImg = LoadGraph("Data/Image/clear.png");
	time = 0;
	ED = false;
	movie = LoadGraph("Data/Movie/ED.ogv");
	PlayMovieToGraph(movie);
}

Child* Clear::update(StateNS::Parent* _parent)
{

	if (ED&& !GetMovieStateToGraph(movie))_parent->moveTo(_parent->NextSequence::SEQ_TITLE);

	if (!saved)
	{
		int nextStage = _parent->stageNum;

		//クリアしたら
		if (nextStage == 53) {
			nextStage = 11;
			ED = true;
		}
		else if (nextStage % 10 == 3)nextStage += 8;
		else ++nextStage;

		saveData->save(nextStage);
		saveData->resetCheckPoint();
		saved = true;
	}
	Child* next = this;


	if (ED)return next;

	if (!prePushUD)
	{

		if (Input_UP())
		{
			--cursorPos;
		}
		if (Input_DOWN())
		{
			++cursorPos;
		}
	}

	cursorPos = (cursorPos + 2) % 2;



	if (Input_OK() && !prePushZ)
	{
		if (cursorPos == 0) {
			int nextStage = _parent->stageNum;

			//クリアしたら
			if (nextStage == 53)nextStage = 11;
			else if (nextStage % 10 == 3)nextStage += 8;
			else ++nextStage;

			_parent->stageNum = nextStage;
			next = new Play(nextStage);
		}
		else if (cursorPos == 1)_parent->moveTo(_parent->NextSequence::SEQ_TITLE);
	}

	prePushUD = Input_UP() || Input_DOWN();
	prePushZ = Input_OK();

	time++;
	time %= 300;
	return next;
}

void Clear::draw() const
{
	DrawGraph(0, 0, backImg, FALSE);
	DrawGraph(-100+time*5, 300, images[12 + (time / 10) % 4], TRUE);
	if (cursorPos == 0)	DrawBox(220, 270, 420, 330, WHITE, FALSE);
	if (cursorPos == 1)	DrawBox(220, 350, 420, 410, WHITE, FALSE);
	if (time < 2)DrawBox(0, 0, 640,480,BLACK,TRUE);
	if (ED)DrawGraph(0, 0, movie, FALSE);
}






}
}

