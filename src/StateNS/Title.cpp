#include "Title.h"
#include "StateParent.h"
#include "..\Data.h"
#include "..\KeyInput.h"
#include "Config.h"
#include "MusicRoom.h"


//for Debug
int hoge[15] = { 11,12,13,21,22,23,31,32,33,41,42,43,51,52,53 };

namespace StateNS{



Title::Title():
save(saveData->getSaveData())
{
	step = 0;
	select = 0;
	initialize();
}


Title::Title(int _step,int _select):
save(saveData->getSaveData())
{
	step = _step;
	select = _select;
	initialize();
}

Title::~Title()
{
	DeleteGraph(mBackImg);
	DeleteGraph(movie);
	sound->deleteSound("titlebgm");
}

void Title::initialize()
{
	count = 0;
	pushZ = false;
	pushX = false;
	pushUP = false;
	pushDOWN = false;
	fontHandle1 = CreateFontToHandle(NULL, 60, 3);
	mBackImg = LoadGraph("Data/Image/Title.png");
	movie = LoadGraph("Data/Movie/OP.ogv");
	PlayMovieToGraph(movie);
	sound->setSound("Data/Sound/OP.wav", "titlebgm");
	sound->playSound("titlebgm", LOOP, false);
}

Child* Title::update(const GrandParent* parent)
{
////////////////////ネストじゃあああああああああ/////////////////////
	Child* next = this;

	//決定音再生
	if(Input_OK() && pushZ)sound->playSound("ok", BACK, true);
	if(Input_NO() && pushX)sound->playSound("no", BACK, true);

	switch (step) {
	case 0:
		if (!GetMovieStateToGraph(movie))step++;
		if (Input_OK())step++;
		break;
	case 1://push z key
		count = (count + 1) % 120;
		if (Input_OK() && pushZ)step++;
		break;
	case 2://ゲームスタート、そうさせつめい
		if (Input_OK() && pushZ) { 
			if (select == 0) { step++; select = 0; }
			else next = nextScene(select);
		}
		if (Input_NO() && pushX)step--;
		else if (Input_UP() && pushUP)select = (select + 3) % 4;
		else if (Input_DOWN() && pushDOWN)select = (select + 1) % 4;
		break;
	case 3:
		if(Input_OK() && pushZ)next = nextScene(0);
		else if (Input_NO() && pushX)step--;
		//else if (Input_UP() && pushUP)select = (select + 2) % 3;
		//else if (Input_DOWN() && pushDOWN)select = (select + 1) % 3;
		else if (Input_UP() && pushUP)select = (select + 14) % 15;
		else if (Input_DOWN() && pushDOWN)select = (select + 1) % 15;
	}

		pushZ = !Input_OK();
	pushX = !Input_NO(); 
	pushUP = !Input_UP();
	pushDOWN = !Input_DOWN();


	return next;
}

void Title::draw() const
{
	switch (step) {
	case 0:
		DrawGraph(0, 0, movie, FALSE);
		break;
	case 1:
		DrawGraph(0, 0, mBackImg, FALSE);
		pressZ_draw();
		break;
	case 2:
		DrawGraph(0, 0, mBackImg, FALSE);
		command_draw();
		break;
	case 3://for Debug
		DrawGraph(0, 0, mBackImg, FALSE);
		DrawBox(200, 280, 440, 420, BLACK, TRUE);

		//*/
		DrawFormatString(250, 300, WHITE, "ステージ%d-%d", hoge[select] / 10, hoge[select]%10);
		DrawFormatString(250, 330, WHITE, "デバッグ用だよ");
		DrawFormatString(250, 360, WHITE, "上下でステージ選択");
		//*/
		
		/*/
		DrawBox(240, 295 + select * 20, 400, 315 + select * 20, GREEN, false);

		DrawFormatString(260, 300, WHITE, "1: ステージ%d-%d", save[0] / 10, save[0] % 10);
		DrawFormatString(260, 320, WHITE, "2: ステージ%d-%d", save[1] / 10, save[1] % 10);
		DrawFormatString(260, 340, WHITE, "3: ステージ%d-%d", save[2] / 10, save[2] % 10);
		DrawFormatString(270, 360, WHITE, "上下でステージ選択");
		//*/

		break;
	}
}

void Title::plusStep(int n) 
{
	step++;
	SetFontSize(n);
}

void Title::pressZ_draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (count - 60)*(count - 60));
	DrawStringToHandle(200, 300, "Press Z", BLACK, fontHandle1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Title::command_draw()const
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(200, 280, 440, 420, BLACK, TRUE);

	DrawFormatString(250, 300, WHITE, "ゲームスタート");
	DrawFormatString(250, 330, WHITE, "みゅーじっくるーむ");
	DrawFormatString(250, 360, WHITE, "せってい");
	DrawFormatString(250, 390, WHITE, "おわる");

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(200, 280, 440, 420, BLACK, FALSE);
	if (select == 0)DrawFormatString(250, 300, WHITE, "ゲームスタート");
	else if (select == 1)DrawFormatString(250, 330, WHITE, "みゅーじっくるーむ");
	else if (select == 2)DrawFormatString(250, 360, WHITE, "せってい");
	else if (select == 3)DrawFormatString(250, 390, WHITE, "おわる");


}


Child* Title::nextScene(int n) {
	Child* scene = 0;
	///////////もっとうまい書き方あったら教えてくれ/////////////////
	switch (n) {
	case 0:scene = new Parent(hoge[select]); break;
	//case 0:scene = new Parent(save[select]); saveData->slotNum = select; break;
	case 1:scene = new MusicRoom(); break;
	case 2:scene = new Config(); break;
	case 3:scene = new Parent(0); break;

	}
	return scene;
}


}