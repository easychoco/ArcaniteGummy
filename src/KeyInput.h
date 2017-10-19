#pragma once

namespace KeyInputNS{


bool Input_Z();
bool Input_X();
bool Input_C();
bool Input_V();
bool Input_W();
bool Input_A();
bool Input_S();
bool Input_D();
bool Input_UP();
bool Input_DOWN();
bool Input_RIGHT();
bool Input_LEFT();
bool Input_RETURN();
bool Input_BACK();
bool Input_ESCAPE();
bool Input_LSHIFT();

bool Input_JUMP();
bool Input_OK();
bool Input_NO();
bool Input_CHANGE();
bool Input_ATTACK();
bool Input_DASH();

void setOK(unsigned);
void setNO(unsigned);
void setATTACK(unsigned);
void setJUMP(unsigned);
void setATTACK(unsigned);
void setJUMP(unsigned);
void setDASH(unsigned);
void setSPECIAL(unsigned);
void setCHANGE(unsigned);
void setPAUSE(unsigned);
void setUP(unsigned);
void setRIGHT(unsigned);
void setDOWN(unsigned);
void setLEFT(unsigned);

/*
extern unsigned INPUT_OK;
extern unsigned INPUT_NO;
extern unsigned INPUT_ATTACK;
extern unsigned INPUT_JUMP;
extern unsigned INPUT_DASH;
extern unsigned INPUT_SPECIAL;
extern unsigned INPUT_CHANGE;
extern unsigned INPUT_PAUSE;
extern unsigned INPUT_UP;
extern unsigned INPUT_RIGHT;
extern unsigned INPUT_DOWN;
extern unsigned INPUT_LEFT;
*/

}

using namespace KeyInputNS;
