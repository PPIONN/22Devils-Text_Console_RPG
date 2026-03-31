#include "Common.h"

// 다른 파일에 있는 4번(전투), 5번(상점) 호출
void scene4();
void scene5();

void sceneLoop() {
	bool isRunning = true;
	while (isRunning) {
		scene4(); // 전투 무한 반복
		scene5(); // 상점 무한 반복

		g_currentFloor++; // 층수 증가 로직 유지

		// 특정 층 도달 시 루프 종료 조건 (예: 10층)
		if (g_currentFloor >= 10) {
			isRunning = false;
		}
	}
}
