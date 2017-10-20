#pragma once
#include <vector>

using namespace std;

namespace MySave
{

class SaveData
{
public:
	//インスタンスのgetter
	static SaveData* getInstance()
	{
		//static変数により初回呼び出し時のみ生成
		static SaveData obj;
		return &obj;
	}

	int slotNum = 0;

	void save(int);
	void saveNewData(int stageNum, int slot);
	const vector<int>& getSaveData() const { return allDatas; }

	//チェックポイントの情報をリセット
	void resetCheckPoint();

	//チェックポイントの情報をセーブ
	void saveCheckPoint(int checkIndex, int switch_flags);

	//参照を使ってチェックポイントの情報をゲット
	void updateCheckPoint(int& _checkIndex, int& _switch_flags);


private:

	//Singleton
	SaveData();
	~SaveData();


	//コピーコンストラクタと代入演算子を明示的にprivateにする
	SaveData(const SaveData &x);
	SaveData& operator=(const SaveData &) {};

	int checkIndex;
	int switch_flags;

	vector<int> allDatas;

	void loadData();
	void outputSaveData();
};


}

using namespace MySave;
