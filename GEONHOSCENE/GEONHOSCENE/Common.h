#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <memory>
#include <algorithm>
#include <cmath>
#include <conio.h>
#include <io.h>
#include <fcntl.h>

using namespace std;

struct Skill {
	string name; string type; string category;
	int power; int accuracy; int pp; int maxPp; int level;
};

enum class StatType { EXP, MaxEXP, Level, Money };
enum class Itemname { Null, RareCandy, HPPotion, FHPPotion, MultiLens, PowerPorion, randomexp, randomgold };

// 전역 변수 (main.cpp 또는 GameSystem.cpp에서 정의)
extern string g_playerName, g_starterName;
extern int g_currentFloor;
class Player;
extern Player g_player;

// 유틸리티 및 씬 함수
void goToXY(int x, int y);
void talk(string name, string text);
void getActualSize(int& width, int& height);
void setFontSize(int size);
void hideCursor();
void initConsole();
wstring s2ws_battle(const string& s);

// 모든 씬 선언
void scene1(); void scene2(); void scene3(); void scene4();
void scene5(); void scene6(); void sceneLoop();
