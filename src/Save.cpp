#include "Save.h"
#include <cassert>
#include <fstream>

namespace MySave{

SaveData::SaveData()
{
	slotNum = 0;
	checkIndex = -10;
	switch_flags = 0;

	loadData();
}

SaveData::~SaveData()
{}

void SaveData::loadData()
{
	ifstream fin;
	fin.open("Data/save.bin", ios::binary | ios::in);

	allDatas.clear();
	allDatas.shrink_to_fit();

	if (!fin)
	{
		allDatas.push_back(11);
		allDatas.push_back(11);
		allDatas.push_back(11);
		fin.close();
		return;
	}
	
	//セーブデータを読み込んでvectorにpush
	int size;
	fin.read((char*)&size, sizeof(int));

	while (size--)
	{
		int stage;
		fin.read((char*)&stage, sizeof(int));
		allDatas.push_back(stage);
	}

	//もしセーブスロットが足りなかったら初期データで埋める
	while (allDatas.size() < 3)
	{
		allDatas.push_back(11);
	}

	allDatas.shrink_to_fit();
	fin.close();
}

void SaveData::outputSaveData()
{
	//ファイル出力
	ofstream fout;
	fout.open("Data/save.bin", ios::binary | ios::out | ios::trunc);

	//vectorのサイズを書き込み
	unsigned size = (int)allDatas.size();
	fout.write((char*)&size, sizeof(int));

	for (const int data : allDatas)
	{
		fout.write((char*)&data, sizeof(int));
	}
	fout.close();
}

//上書きオートセーブ
void SaveData::save(int _stageNum)
{
	allDatas[slotNum] = _stageNum;
}

//別スロットへのセーブ
void SaveData::saveNewData(int _stageNum, int _slot)
{
	if (_slot < (int)allDatas.size())allDatas[_slot] = _stageNum;
	else assert("Save:: slot範囲外");

	this->slotNum = _slot;
}

void SaveData::resetCheckPoint()
{
	checkIndex = -10;
	switch_flags = 0;
}

void SaveData::saveCheckPoint(int _checkIndex, int _switch_flags)
{
	checkIndex = _checkIndex;
	switch_flags = _switch_flags;
}

void SaveData::updateCheckPoint(int& _checkIndex, int& _switch_flags)
{
	_checkIndex = checkIndex;
	_switch_flags = switch_flags;
}



}
