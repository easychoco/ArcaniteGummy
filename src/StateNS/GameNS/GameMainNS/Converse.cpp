#include "Converse.h"

#include "GameMain.h"
#include "..\..\..\KeyInput.h"
#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

/////////ステージごとにテキストで分割。


Converse::Converse(GameMain* _main, int _stageNum1,int _stageNum2)
{
	main = _main;
	stageNum = _stageNum1 * 10 + _stageNum2;
	initialize();
}

Converse::~Converse()
{

}


void Converse::initialize()
{
	passageNum = 0;
	prePush = false;

	string textFile = "Data/Text/Converse/stage";
	textFile += std::to_string(stageNum);
	textFile += ".txt";

	std::ifstream fin(textFile);
	assert(fin && "会話データ読み込みエラー");

	string name, serifu;
	while (fin >> name >> serifu) {
		allPassages.push_back(Passage(name, YennToCR(serifu)));
	}



	//for Debug
//	allPassages.push_back(Passage("sakuya", "tesてすテスト\n忠誠心は鼻から出る\n\nこ　ん　に　ち　は"));
}

Child* Converse::update(GameParent* _parent)
{
	Child* next = this;

	bool finish = false;
	if (Input_Z() && !prePush)finish = nextPassage();

	prePush = Input_Z();

	//for Debug
	if (Input_Z() && !prePush)
		passageNum++;
	if (CheckHitKey(KEY_INPUT_2) || passageNum>=allPassages.size())
		next = main;
	
	prePush = Input_Z();

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
	DrawFormatString(560, 320, WHITE, "%d / %d", passageNum + 1, allPassages.size());
}



//==============================================
//内部プライベートメンバ
//==============================================
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

	//フレーム表示
	DrawBox(10, 250, 150, 290, BLACK, true);
	DrawBox(10, 300, 630, 470, BLACK, true);
	//枠
	DrawBox(10, 250, 150, 290, WHITE, false);
	DrawBox(10, 300, 630, 470, WHITE, false);

	DrawString(480, 450, "press Z to next", WHITE);

	//文章表示

	//名前
	DrawString(20, 260, speaker.c_str(), WHITE);
	//文章
	DrawString(20, 320, passage.c_str(), WHITE);
}

bool Converse::nextPassage()
{
	++passageNum;
	if (passageNum >= allPassages.size())
	{
		passageNum = allPassages.size() - 1;
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

	while (std::string::npos != pos) {
		s.replace(pos, YenN.length(), CR);
		pos = s.find_first_of(YenN, pos);
	}

	return s;
}




}
}
}
