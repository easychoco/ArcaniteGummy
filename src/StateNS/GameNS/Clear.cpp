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
	sound->deleteSound("clear");
	saveData->outputSaveData();
	DeleteGraph(backImg);
	for (int i = 0; i < 32; i++)
	{
		DeleteGraph(images[i]);
	}
}

void Clear::initialize()
{
	saved = false;
	prePushZ = true;
	prePushUD = true;
	cursorPos = 0;
	sound->setSound("Data/Sound/clear.mp3", "clear");
	sound->playSound("clear");
	LoadDivGraph("Data/Image/chip_mokou.png", 32, 8, 4, 32, 64, images, TRUE);
	assert(*images != -1 && "���@�摜�ǂݍ��݃G���[");
	backImg = LoadGraph("Data/Image/clear.png");
	time = 0;
	ED = false;
}

Child* Clear::update(StateNS::Parent* _parent)
{
	if (ED&& !GetMovieStateToGraph(movie))_parent->moveTo(_parent->NextSequence::SEQ_TITLE);

	//�܂��Z�[�u�O�Ȃ�
	if (!saved)
	{
		int nextStage = _parent->stageNum;

		//�N���A������
		if (nextStage == 53) {
			nextStage = 52;
			ED = true;
			movie = LoadGraph("Data/Movie/ED.ogv");
			sound->stopSoundOfFile();
			PlayMovieToGraph(movie);
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

			//�N���A������
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
	return next;
}

void Clear::draw() const
{
	if (ED)DrawGraph(0, 0, movie, FALSE);
	else if(time > 5)
	{
		DrawGraph(0, 0, backImg, FALSE);
		if (cursorPos == 0)	DrawBox(220, 270, 420, 330, RED, FALSE);
		if (cursorPos == 1)	DrawBox(220, 350, 420, 410, RED, FALSE);
		//if (time < 2)DrawBox(0, 0, 640,480,BLACK,TRUE);
		DrawGraph(-100 + time * 5, 300, images[12 + (time / 10) % 4], TRUE);
	}
}






}
}

