#include "Pause.h"
#include "..\..\StateParent.h"


#include "GameMain.h"
#include "..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Pause::Pause(GameMain* _main)
{
	main = _main;
	initialize();
}

Pause::~Pause()
{

}

void Pause::initialize()
{
	prePush = true;
	originalCameraPos = main->getCameraPos();
}

Child* Pause::update(GameParent* _parent)
{
	Child* next = this;

	bool exit = false;

	int dx = (Input_RIGHT() - Input_LEFT()) * 10;
	int dy = (Input_DOWN() - Input_UP()) * 10;

	main->moveCamera(dx, dy);
	if (Input_A() && !prePush)
		next = main;

	

	prePush = Input_A();
	return next;
}

void Pause::draw() const
{
	main->draw();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
	DrawBox(0, 0, 640, 480, BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);
}





}
}
}

