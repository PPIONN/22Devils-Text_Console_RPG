#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>

using namespace std;

// [외부 참조 선언 - main.cpp의 것을 빌려씀]
extern void goToXY(int x, int y);
extern void setFontSize(int size);
extern void getActualSize(int& width, int& height);
extern void hideCursor();
extern string g_playerName;
extern string g_starterName;
extern int g_playerHP, g_playerMaxHP, g_playerGold, g_potionCount;

// [수정] 유니코드 모드에서도 안전하게 화면을 지우도록 변경
void fadeOut(int lines, int cols) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < lines; i++) {
		SetConsoleCursorPosition(hConsole, { 0, (SHORT)i });
		for (int j = 0; j < cols; j++) {
			// [핵심] 일반 printf 대신 wcout을 사용하여 충돌 방지
			wcout << L" ";
		}
		// 출력 속도가 너무 느리면 숫자를 1~2로 줄이세요
		Sleep(5);
	}
	system("cls");
}

void scene1() {
	hideCursor();

	// 1. 유니코드 모드 설정
	_setmode(_fileno(stdout), _O_U16TEXT);

	// 2. 폰트 설정 (이미지 보니까 30~35 정도가 적당해 보입니다)
	setFontSize(30);

	// [중요] system("mode con...")은 절대 쓰지 마세요. main의 설정을 따릅니다.

	wcout << LR"(
             ██████╗  ██████╗ ██╗  ██╗███████╗██████╗  ██████╗  ██████╗ ██╗   ██╗███████╗
             ██╔══██╗██╔═══██╗██║ ██╔╝██╔════╝██╔══██╗██╔═══██╗██╔════╝ ██║   ██║██╔════╝
             ██████╔╝██║   ██║█████╔╝ █████╗  ██████╔╝██║   ██║██║  ███╗██║   ██║█████╗  
             ██╔═══╝ ██║   ██║██╔═██╗ ██╔══╝  ██╔══██╗██║   ██║██║   ██║██║   ██║██╔══╝  
             ██║     ╚██████╔╝██║  ██╗███████╗██║  ██║╚██████╔╝╚██████╔╝╚██████╔╝███████╗
             ╚═╝      ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝ ╚═════╝  ╚═════╝  ╚═════╝ ╚══════╝

             Press any key to start!

                                                            조원: 오채율, 신건호, 이현준
                                                                  이채호, 배건우, 노용수 
    )" << endl;

	// 3. 입력 대기 (이후 fadeOut 실행)
	system("pause > nul");

	int currW, currH;
	getActualSize(currW, currH);

	// 4. 안전하게 페이드 아웃 실행
	fadeOut(currH, currW);

	// 5. [중요] 다른 Scene으로 넘어가기 전 반드시 일반 모드로 복구
	_setmode(_fileno(stdout), _O_TEXT);
}
