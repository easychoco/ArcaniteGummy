#include "Save.h"
#include <cassert>
#include <fstream>

namespace MySave{

SaveData::SaveData()
{
	hp = 100;
	clearStage = 0;
}

SaveData::~SaveData()
{

}

void SaveData::loadData()
{
	ifstream fin("save.txt");

	allDatas.clear();

	//セーブデータを読み込んでvectorにpush
	int stage = 0;
	while (fin >> stage, stage)
	{
		allDatas.push_back(stage);
	}
	
	allDatas.shrink_to_fit();
}

void SaveData::saveData()
{
	int save_hp = hp * 2;
	int save_clearStage = hp * 2;

	//fout << save_hp << " " << save_left << " " << save_clearStage << endl;
}




}
