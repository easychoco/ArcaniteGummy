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
	bool exists(string name) { return soundMap.find(name) != soundMap.end(); }

public:
	//インスタンスのgetter
	static Sound* getInstance()
	{
		//static変数により初回呼び出し時のみ生成
		static Sound obj;
		return &obj;
	}

	void setSound(string path, string name);
	void deleteSound(string name);
	void playSound(string name, PlayType);
	void playSoundWithPath(string path, PlayType);
	void StopSound(string name);
	void stopAllSound();
	void setVolume(string name, float ratio);
	void setAllVolume(float ratio);
};

static Sound* sound;

}

using namespace MySound;
