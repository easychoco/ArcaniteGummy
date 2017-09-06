#include "Config.h"
#include "StateParent.h"
#include "..\Data.h"
#include "..\KeyInput.h"


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
	return next;
}

void Config::draw() const
{
	DrawFormatString(0, 0, WHITE, "configggggg");
	//DrawGraph(0, 0, graph[0], FALSE);

}




}