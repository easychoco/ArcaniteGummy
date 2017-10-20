#include "Converse.h"

#include "GameMain.h"
#include "..\..\..\KeyInput.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

/////////ステージごとにテキストで分割。


Converse::Converse(GameMain* _main, int _stageNum)
{
	main = _main;
	stageNum = _stageNum;
	initialize();
	prePush = true;
	initial_cancel = Input_NO();
}

Converse::~Converse()
{

}

void Converse::initialize()
{
	passageNum = 0;
	prePush = false;

	initial_cancel = true;
	
	string textFile = "Data/Text/Converse/stage";
	textFile += std::to_string(stageNum);
	textFile += ".txt";

	std::ifstream fin(textFile);
	assert(fin && "会話データ読み込みエラー");

	string name, serifu;
	while (fin >> name >> serifu) {
		allPassages.push_back(Passage(name, YennToCR(serifu)));
	}

}

Child* Converse::update(GameParent* _parent)
{
	Child* next = this;

	bool finish = false;
	if (initial_cancel)initial_cancel = Input_NO();
	if ((Input_OK() && !prePush) || (Input_NO() && !initial_cancel))finish = nextPassage();

	prePush = Input_OK();

	if (finish)next = main;

	return next;
}

void Converse::draw() const
{
	main->draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, 640, 480, BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	allPassages[passageNum].show();

	//for Debug
	DrawFormatString(560, 80, WHITE, "%d / %d", passageNum + 1, allPassages.size());
}



//==============================================
//内部プライベートメンバ
//==============================================
bool Converse::nextPassage()
{
	++passageNum;
	if (passageNum >= allPassages.size())
	{
		passageNum = (int)allPassages.size() - 1;
		return true;
	}
	return false;
}


string Converse::YennToCR(string str)
{
	string s = str;
	string YenN = "\\n";
	string CR = "\n";

	std::string::size_type pos = s.find_first_of(YenN, 0);

	while (std::string::npos != pos)
	{
		s.replace(pos, YenN.length(), CR);
		pos = s.find_first_of(YenN, pos);
	}

	return s;
}


Converse::Passage::Passage(string _speaker, string _passage)
{
	speaker = _speaker;
	passage = _passage;
}

Converse::Passage::~Passage()
{

}

void Converse::Passage::show() const
{
	//for Debug
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	//フレーム表示
	DrawBox(10, 10, 150, 50, BLACK, true);
	DrawBox(10, 60, 630, 210, BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//枠
	DrawBox(10, 10, 150, 50, WHITE, false);
	DrawBox(10, 60, 630, 210, WHITE, false);


	DrawString(400, 170, "      決定ボタンで次へ", WHITE);
	DrawString(400, 190, "キャンセルボタンでスキップ", WHITE);

	//文章表示

	//名前
	DrawString(20, 20, speaker.c_str(), WHITE);
	//文章
	DrawString(20, 80, passage.c_str(), WHITE);
}



}
}
}
