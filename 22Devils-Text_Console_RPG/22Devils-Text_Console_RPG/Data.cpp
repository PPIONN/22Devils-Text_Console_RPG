#include <string>
#include "GameData.h"

using namespace std;

// 모든 전역 변수의 '실제 저장소' (본체이므로 extern을 붙이지 않음)
string g_playerName = "플레이어";
string g_starterName = "이상해씨";
int g_playerHP = 100;
int g_playerMaxHP = 100;
int g_playerGold = 500;
int g_potionCount = 1;
int g_currentFloor = 1;
int g_playerLevel = 1;
int g_playerExp = 0;

// [수정] Player 객체의 진짜 본체입니다.
Player g_player;
