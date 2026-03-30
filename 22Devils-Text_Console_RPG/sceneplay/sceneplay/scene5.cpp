#include <iostream>
#include <string>
#include <windows.h>



using namespace std;

extern void goToXY(int x, int y);
extern void getActualSize(int& width, int& height);
extern void talk(string name, string text);
extern int g_playerGold;   // main.cpp 전역 변수
extern int g_playerHP;     // main.cpp 전역 변수
extern int g_playerMaxHP;
extern int g_potionCount;

void scene5() {
	int w, h;
	getActualSize(w, h);
	bool inShop = true;

	while (inShop) {
		system("cls");
		int midX = w / 2 - 25;
		int midY = h / 2 - 5;

		goToXY(midX, midY);     cout << "==================================================";
		goToXY(midX, midY + 1); cout << "             [ 포켓몬 센터 & 상점 ]               ";
		goToXY(midX, midY + 2); cout << "    현재 HP: " << g_playerHP << "/" << g_playerMaxHP;
		goToXY(midX, midY + 3); cout << "    소지금 : " << g_playerGold << " Gold | 상처약: " << g_potionCount << "개";
		goToXY(midX, midY + 4); cout << "==================================================";
		goToXY(midX, midY + 6); cout << "  1. 전 회복 (300 Gold)";
		goToXY(midX, midY + 7); cout << "  2. 상처약 구매 (150 Gold)";
		goToXY(midX, midY + 8); cout << "  3. 다음 층으로 이동하기 (나가기)";
		goToXY(midX, midY + 10); cout << "  선택: ";

		int choice;
		if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }

		if (choice == 1) {
			if (g_playerGold >= 300) {
				g_playerGold -= 300;
				g_playerHP = g_playerMaxHP;
				cout << "\n    >> 몸이 가벼워졌습니다! HP가 모두 회복되었습니다.";
			}
			else cout << "\n    >> 골드가 부족합니다!";
			Sleep(1000);
		}
		else if (choice == 2) {
			if (g_playerGold >= 150) {
				g_playerGold -= 150;
				g_potionCount++;
				cout << "\n    >> 상처약을 구매했습니다!";
			}
			else cout << "\n    >> 골드가 부족합니다!";
			Sleep(1000);
		}
		else if (choice == 3) {
			cout << "\n    >> 모험을 계속합니다...";
			Sleep(1000);
			inShop = false;
		}
	}
}
