#include <iostream>
#include <string>
#include <windows.h>


using namespace std;

extern void scene4();      // 기존 전투 장면
extern void scene5();       // 상점 장면
extern void talk(string name, string text);
extern int g_currentFloor; // 현재 층수
extern int g_playerHP;

void scene6() {
	bool isAlive = true;

	// 플레이어가 살아있는 동안 무한 반복
	while (isAlive) {
		system("cls");

		// 1. 층수 안내
		string floorMsg = to_string(g_currentFloor) + "층에 진입합니다...";
		talk("시스템", floorMsg);

		// 2. 전투 실행 (scene4 내부에서 적의 레벨이 g_currentFloor에 맞춰지도록 수정 권장)
		scene4();

		// 3. 전투 후 생존 체크
		if (g_playerHP <= 0) {
			system("cls");
			talk("시스템", "눈앞이 캄캄해졌다... 모험이 끝났습니다.");
			isAlive = false;
			break;
		}

		// 4. 전투 승리 후 정비 (상점 방문)
		talk("나", "다음 층으로 가기 전에 정비를 좀 해야겠어.");
		scene5();

		// 5. 다음 층으로 난이도 상승
		g_currentFloor++;

		// 특정 층 도달 시 이벤트 (예: 5층 단위)
		if (g_currentFloor % 5 == 0) {
			talk("오박사", "자네, 벌써 " + to_string(g_currentFloor) + "층인가? 대단하구만!");
		}
	}
}
