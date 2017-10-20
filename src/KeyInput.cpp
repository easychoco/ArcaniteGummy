#include "KeyInput.h"
#include "DXLib.h"

#include <fstream>

const bool toBoolean[2]{ false, true };

//以下のコマンドで設定
//INPUT_C = (GetJoypadInputState(DX_INPUT_PAD1));
unsigned INPUT_OK = 16;
unsigned INPUT_NO = 32;
unsigned INPUT_ATTACK = 16;
unsigned INPUT_JUMP = 32;
unsigned INPUT_DASH = 64;
unsigned INPUT_SPECIAL = 128;
unsigned INPUT_CHANGE = 4096;
unsigned INPUT_PAUSE = 8192;
unsigned INPUT_UP = 65536;
unsigned INPUT_RIGHT = 131072;
unsigned INPUT_DOWN = 262144;
unsigned INPUT_LEFT = 524288;




namespace KeyInputNS{

bool Input_Z()
{
	return toBoolean[CheckHitKey(KEY_INPUT_Z)];
}

bool Input_X()
{
	return toBoolean[CheckHitKey(KEY_INPUT_X)];
}

bool Input_C()
{
	return toBoolean[CheckHitKey(KEY_INPUT_C)] | ((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_SPECIAL) > 0);
}

bool Input_V()
{
	return toBoolean[CheckHitKey(KEY_INPUT_V)];
}

bool Input_W()
{
	return toBoolean[CheckHitKey(KEY_INPUT_W)];
}

bool Input_A()
{
	return toBoolean[CheckHitKey(KEY_INPUT_A)] | ((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_PAUSE) > 0);
}

bool Input_S()
{
	return toBoolean[CheckHitKey(KEY_INPUT_S)];
}

bool Input_D() 
{
	return toBoolean[CheckHitKey(KEY_INPUT_D)];
}

bool Input_UP()
{
	return toBoolean[CheckHitKey(KEY_INPUT_UP)] | ((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_UP) > 0);
}

bool Input_DOWN() 
{
	return toBoolean[CheckHitKey(KEY_INPUT_DOWN)] | ((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_DOWN) > 0);
}

bool Input_RIGHT()
{
	return toBoolean[CheckHitKey(KEY_INPUT_RIGHT)] | ((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_RIGHT) > 0);
}

bool Input_LEFT()
{
	return toBoolean[CheckHitKey(KEY_INPUT_LEFT)] | ((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_LEFT) > 0);
}

bool Input_RETURN()
{
	return toBoolean[CheckHitKey(KEY_INPUT_RETURN)];
}

bool Input_BACK()
{
	return toBoolean[CheckHitKey(KEY_INPUT_BACK)];
}

bool Input_ESCAPE()
{
	return toBoolean[CheckHitKey(KEY_INPUT_ESCAPE)];
}

bool Input_LSHIFT()
{
	return toBoolean[CheckHitKey(KEY_INPUT_LSHIFT)];
}

bool Input_JUMP()
{
	return toBoolean[CheckHitKey(KEY_INPUT_SPACE)] || toBoolean[CheckHitKey(KEY_INPUT_X)] | ((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_JUMP) > 0);
}

bool Input_OK()
{
	return toBoolean[CheckHitKey(KEY_INPUT_Z)] | ((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_OK) > 0);
}

bool Input_NO()
{
	return toBoolean[CheckHitKey(KEY_INPUT_X)] | ((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_NO) > 0);
}

bool Input_CHANGE()
{
	return toBoolean[CheckHitKey(KEY_INPUT_RETURN)] | ((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_CHANGE) > 0);
}

bool Input_ATTACK()
{
	return toBoolean[CheckHitKey(KEY_INPUT_Z)] | ((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_ATTACK) > 0);
}

bool Input_DASH()
{
	return toBoolean[CheckHitKey(KEY_INPUT_LSHIFT)] | ((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_DASH) > 0);
}


void setOK(unsigned _in)
{
	INPUT_OK = _in;
}

void setNO(unsigned _in)
{
	INPUT_NO = _in;
}

void setATTACK(unsigned _in)
{
	INPUT_ATTACK = _in;
}

void setJUMP(unsigned _in)
{
	INPUT_JUMP = _in;
}

void setDASH(unsigned _in)
{
	INPUT_DASH = _in;
}

void setSPECIAL(unsigned _in)
{
	INPUT_SPECIAL = _in;
}

void setCHANGE(unsigned _in)
{
	INPUT_CHANGE = _in;
}

void setPAUSE(unsigned _in)
{
	INPUT_PAUSE = _in;
}

void setUP(unsigned _in)
{
	INPUT_UP = _in;
}

void setRIGHT(unsigned _in)
{
	INPUT_RIGHT = _in;
}

void setDOWN(unsigned _in)
{
	INPUT_DOWN = _in;
}

void setLEFT(unsigned _in)
{
	INPUT_LEFT = _in;
}

void loadKeyConfig()
{
	std::ifstream fin("keyinput.txt");

	//ファイルがなければreturn
	if (!fin)return;

	fin >> INPUT_OK;
	fin >> INPUT_NO;
	fin >> INPUT_ATTACK;
	fin >> INPUT_JUMP;
	fin >> INPUT_DASH;
	fin >> INPUT_SPECIAL;
	fin >> INPUT_CHANGE;
	fin >> INPUT_PAUSE;
	fin >> INPUT_UP;
	fin >> INPUT_RIGHT;
	fin >> INPUT_DOWN;
	fin >> INPUT_LEFT;
}

void saveKeyConfig()
{
	std::ofstream fout("keyinput.txt");
	using std::endl;

	fout << INPUT_OK << endl;
	fout << INPUT_NO << endl;
	fout << INPUT_ATTACK << endl;
	fout << INPUT_JUMP << endl;
	fout << INPUT_DASH << endl;
	fout << INPUT_SPECIAL << endl;
	fout << INPUT_CHANGE << endl;
	fout << INPUT_PAUSE << endl;
	fout << INPUT_UP << endl;
	fout << INPUT_RIGHT << endl;
	fout << INPUT_DOWN << endl;
	fout << INPUT_LEFT << endl;

}




}
