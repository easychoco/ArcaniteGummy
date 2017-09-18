#include "DxLib.h"
#include "Data.h"
#include "KeyInput.h"
#include "Parent.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	SetMainWindowText("ArcGum");

	Parent* parent = new Parent();

	//マップチップ読み込み
	int tmp = LoadDivGraph("Data/Image/MapChip.png", 256, 16, 16, 32, 32, MyData::MapChip);
	assert(tmp != -1 && "マップチップ読み込みエラー");

	while (!ProcessMessage() && !Input_ESCAPE())
	{
		ClearDrawScreen();

		parent->update();
		parent->draw();

		ScreenFlip();
	}

	InitGraph();

	DxLib_End();
	return 0;
}