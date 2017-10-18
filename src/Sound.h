#pragma once

#include "DXLib.h"
#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

namespace MySound
{

enum PlayType
{
	BACK,
	LOOP,
	NORMAL,
};


//Singletonで実装
class Sound
{
private:
	Sound() {};
	~Sound() {};

	//コピーコンストラクタと代入演算子を明示的にprivateにする
	Sound(const Sound &x);
	Sound& operator=(const Sound &);

	unordered_map<string, int> soundMap;

public:
	float allVolume = 1.0f;

	//インスタンスのgetter
	static Sound* getInstance()
	{
		//static変数により初回呼び出し時のみ生成
		static Sound obj;
		return &obj;
	}

	void setSound(string path, string name);
	void deleteSound(string name);

	//BACK、多重不可で再生
	void playSound(string name);

	//多重で再生させない
	void playSound(string name, PlayType);

	//key, 再生スタイル, 多重で再生できるかどうか
	void playSound(string name, PlayType, bool coverable);
	void playSoundWithPath(string path, PlayType);
	void stopSound(string name);
	void stopSoundOfFile();
	void stopAllSound();
	void setVolume(string name, float ratio);
	void setAllVolume(float ratio);
	bool exists(string name) { return soundMap.find(name) != soundMap.end(); }
};

}

using namespace MySound;
