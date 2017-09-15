#include "Title.h"
#include "StateParent.h"
#include "..\Data.h"
#include "..\KeyInput.h"
#include "Config.h"
#include "MusicRoom.h"

namespace StateNS{


Title::Title()
{
	step = 0;
	select = 0;
	initialize();
}


Title::Title(int _step,int _select)
{
	step = _step;
	select = _select;
	initialize();
}

Title::~Title()
{

}

void Title::initialize()
{
	count = 0;
	pushZ = false;
	pushUP = false;
	pushDOWN = false;
	fontHandle1 = CreateFontToHandle(NULL, 60, 3);
	mBackImg = LoadGraph("Data/Image/Title.png");
	movie = LoadGraph("Data/Movie/OP.ogv");
	PlayMovieToGraph(movie);
}

Child* Title::update(const GrandParent* parent)
{
////////////////////ネストじゃあああああああああ/////////////////////
	Child* next = this;
	switch (step) {
	case 0:
		if (!GetMovieStateToGraph(movie))step++;
		if (Input_Z())step++;
		break;
	case 1://push z key
		//SeekMovieToGraph(movie, 6000);
		count = (count + 1) % 120;
		if (Input_Z() && pushZ)step++;
		break;
	case 2://ゲームスタート、そうさせつめい
//		SeekMovieToGraph(movie, 6000);
		if (Input_Z() && pushZ)next = nextScene(select);

		if (Input_UP() && pushUP)select = (select + 3) % 4;
		if (Input_DOWN() && pushDOWN)select = (select + 1) % 4;
		break;
	}

	
	if (!Input_Z())pushZ = true;
	else pushZ = false;

	if (!Input_UP())pushUP = true;
	else pushUP = false;

	if (!Input_DOWN())pushDOWN = true;
	else pushDOWN = false;


	return next;
}

void Title::draw() const
{
	DrawFormatString(0, 0, WHITE, "Titleeeeee");
	DrawGraph(0, 0, movie, FALSE);

	switch (step) {
	case 1:
		DrawGraph(0, 0, mBackImg, FALSE);
		pressZ_draw();
		break;
	case 2:
		DrawGraph(0, 0, mBackImg, FALSE);
		command_draw();
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
	Child* scene;
	///////////もっとうまい書き方あったら教えてくれ/////////////////
	switch (n) {
	case 0:scene = new Parent(); break;
	case 1:scene = new MusicRoom(); break;
	case 2:scene = new Config(); break;
	case 3:scene = new Parent(); break;

	}
	return scene;
}


}