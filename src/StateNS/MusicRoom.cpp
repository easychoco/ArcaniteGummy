#include "MusicRoom.h"
#include "StateParent.h"
#include "..\Data.h"
#include "..\KeyInput.h"
#include "Title.h"


namespace StateNS{



MusicRoom::MusicRoom()
{
	initialize();
}

MusicRoom::~MusicRoom()
{

}

void MusicRoom::initialize()
{

}

Child* MusicRoom::update(const GrandParent* parent)
{
	Child* next = this;
	if (Input_NO())next = new StateNS::Title(2,1);
	return next;
}

void MusicRoom::draw() const
{
	DrawFormatString(0, 0, WHITE, "musicroom X‚Å–ß‚ê‚é‚æ");

	//DrawGraph(0, 0, graph[0], FALSE);

}




}