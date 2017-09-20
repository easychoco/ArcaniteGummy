#include "Save.h"
#include <cassert>
#include <fstream>

namespace MySave{

SaveData::SaveData()
{
	hp = 100;
	left = 1;
	clearStage = 0;
}

SaveData::~SaveData()
{

}

Data SaveData::loadData()
{
	/*
	this->hp = (int)(arg[0] / 2);
	this->left = (int)(arg[1] / 2);
	this->clearStage = (int)(arg[2] / 2);
	*/

	//if (data.inValid)assert("ƒ[ƒh¸”s");

	return Data{ hp, left, clearStage };
}

void SaveData::saveData()
{
	int save_hp = hp * 2;
	int save_left = hp * 2;
	int save_clearStage = hp * 2;

	//fout << save_hp << " " << save_left << " " << save_clearStage << endl;
}

void SaveData::setSaveData(Data _data)
{
	this->hp = _data.hp;
	this->left = _data.left;
	this->clearStage = _data.clearStage;
}


}
