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

}

void Config::initialize()
{

}

Child* Config::update(const GrandParent* parent)
{
	Child* next = this;
	if (Input_X())next = new StateNS::Title(2,2);
	return next;
}

void Config::draw() const
{
	DrawFormatString(0, 0, WHITE, "configggggg X‚Å–ß‚ê‚é‚æ");

	//DrawGraph(0, 0, graph[0], FALSE);

}




}