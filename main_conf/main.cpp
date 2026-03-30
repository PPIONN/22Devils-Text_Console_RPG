#include <iostream>
#include <windows.h>
#include <string>
#include "Player.h"

using namespace std;

// 기존의 전역 변수를 이제 모두 플레이어가 관리
Player* player = nullptr;
int g_currentfloor = 1;    // 현재 공략 중인 층수
// ----------------------------

// 장면 함수 선언
void scene1();
void scene2();
void scene3();
void scene4();
void scene5(); // [추가] 상점
void scene6(); // [추가] 반복 루프 관리(4+5 반복)

// [도구 1] 커서 이동
void goToXY(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hConsole, pos);
}

// [도구 2] 폰트 설정
void setFontSize(int size) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = size;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

// [도구 3] 화면 크기 가져오기
void getActualSize(int& width, int& height) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// [도구 4] 커서 가리기
void hideCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void disableQuickEdit() {
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prev_mode;
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE & ~ENABLE_MOUSE_INPUT);
}

int main() {
	system("mode con: cols=250 lines=300");
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
	disableQuickEdit();

	scene1(); // 오프닝
	scene2(); // 이름 및 포켓몬 선택
	scene3(); // 탑 진입 애니메이션

	// scene4(); // 단발성 전투 대신 아래 scene6에서 반복되도록 구조를 잡습니다.

	scene6(); // [핵심] 여기서 4번(전투)과 5번(상점)이 무한 루프로 돌아갑니다.

	system("cls");
	goToXY(0, 0);
	cout << "모험이 끝났습니다. 게임을 종료하려면 아무 키나 누르세요...";
	system("pause > nul");

	//종료 시 메모리 해제
	if (player)
	{
		delete player;
	}
	return 0;
}
