#pragma once
#include <vector>

using namespace std;

namespace MySave
{

class SaveData
{
public:
	SaveData();
	~SaveData();
	void save(int);
	void loadData();
	const vector<int>& getSaveData() const { return allDatas; }

private:
	int hp;
	int left;
	int clearStage;
	vector<int> allDatas;
};


}

using namespace MySave;
