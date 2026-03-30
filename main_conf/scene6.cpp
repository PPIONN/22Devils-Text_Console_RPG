#include <iostream>
#include <string>
#include <windows.h>
#include "Player.h"

using namespace std;

extern void scene4();      // 기존 전투 장면
extern void scene5();      // 상점 장면
extern void talk(string name, string text);
extern int g_currentfloor; // 현재 층수
extern Player* player;

void scene6() {
	bool IsGameOver = false;

	while (IsGameOver) {
		// 1. 층수 증가 및 진입 안내
		system("cls");
		string floorMsg = to_string(g_currentfloor) + "층에 진입합니다...";
		talk("시스템", floorMsg);

		// 2. 전투 실행
		scene4();

		// 3. 전투 후 생존 체크 (전체 포켓몬 체크로 확장 권장)
		if (player->isAllFainted())
		{
			system("cls");
			talk("시스템", "모든 포켓몬이 기절했습니다...");
			talk("시스템", "눈앞이 캄캄해졌다! 모험이 끝났습니다.");
			IsGameOver = true;
			break;
		}

		// 4. 정비 및 다음 층 결정
		talk("나", "다음 층으로 가기 전에 정비를 좀 해야겠어.");
		scene5(); // scene5 내부에서 "게임 종료"를 선택하면 IsGameOver를 false로 바꿀 수 있게 설계할 필요가 있다.

		// 5. 난이도 상승 및 이벤트
		if (g_currentfloor % 5 == 0) {
			talk("오박사", "자네, 벌써 " + to_string(g_currentfloor) + "층인가? 대단하구만!");
		}

		g_currentfloor++;
	}
}
