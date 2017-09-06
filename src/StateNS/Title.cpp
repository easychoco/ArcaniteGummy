#include "Title.h"
#include "StateParent.h"
#include "..\Data.h"
#include "..\KeyInput.h"
#include "Config.h"


namespace StateNS{



Title::Title()
{
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
	step = 0;
	select = 0;
}

Child* Title::update(const GrandParent* parent)
{
////////////////////ネストじゃあああああああああ/////////////////////
	Child* next = this;
	switch (step) {
	case 0://push z key
		count = (count + 1) % 120;
		if (Input_Z() && pushZ)step++;
		break;
	case 1://ゲームスタート、そうさせつめい
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
	//DrawGraph(0, 0, graph[0], FALSE);
	//////////////////////////////////////////////////////これはひどいコード/////////////////////////////////////
	switch (step) {
	case 0:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (count - 60)*(count - 60));
		//DrawGraph(0, 0, graph[1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case 1:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawFormatString(250, 300, WHITE, "ゲームスタート");
		DrawFormatString(250, 330, WHITE, "みゅーじっくるーむ");
		DrawFormatString(250, 360, WHITE, "せってい");
		DrawFormatString(250, 390, WHITE, "おわる");

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if(select==0)DrawFormatString(250, 300, WHITE, "ゲームスタート");
		else if(select==1)DrawFormatString(250, 330, WHITE, "みゅーじっくるーむ");
		else if(select==2)DrawFormatString(250, 360, WHITE, "せってい");
		else if(select==3)DrawFormatString(250, 390, WHITE, "おわる");

		break;
	}
}

Child* Title::nextScene(int n) {
	Child* scene;
	///////////もっとうまい書き方あったら教えてくれ/////////////////
	switch (n) {
	case 0:scene = new Parent(); break;
	case 1:scene = new Parent(); break;
	case 2:scene = new StateNS::Config(); break;
	case 3:scene = new Parent(); break;

	}
	return scene;
}


}