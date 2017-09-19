#pragma once



namespace MySave
{


/*
Memento
メンバ変数
・機数
・クリア状況（bool?int? まかせた）
・（コイン枚数）
*/

struct Data
{
	int hp;//体力
	int left;//残機
	int clearStage;//クリア済みのステージ
};

//Singletonで実装
class SaveData
{
public:
	SaveData() {};
	~SaveData() {};
	Data loadData();
	void saveData();
	void setSaveData(Data);

private:
	int hp;
	int left;
	int clearStage;

};


}

using namespace MySave;
