#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;

// Utils.cpp 유틸리티 함수
void goToXY(int x, int y);
void setFontSize(int size);
void getActualSize(int& width, int& height);
void hideCursor();
void initConsole();
void talk(string name, string text);

// 씬 함수들
void scene1(); void scene2(); void scene3();
void scene4(); void scene5(); void scene6();
void sceneLoop();

// Data.cpp 전역 변수들
extern string g_playerName, g_starterName;
extern int g_playerHP, g_playerMaxHP, g_playerGold, g_potionCount, g_currentFloor, g_playerLevel, g_playerExp;
