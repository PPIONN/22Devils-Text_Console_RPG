#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

// [전역 변수]
string g_playerName = "플레이어";
string g_starterName = "이상해씨";
int g_playerHP = 100;
int g_playerMaxHP = 100;
int g_playerGold = 500;
int g_potionCount = 1;
int g_currentFloor = 1;

// 장면 함수 선언
void scene1(); void scene2(); void scene3();
void scene4(); void scene5(); void scene6();

// --- [기존 scene 파일들이 사용하는 도구들 - 삭제하면 에러남] ---

void goToXY(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hConsole, pos);
}

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

void getActualSize(int& width, int& height) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void hideCursor() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// ---------------------------------------------------------

void initConsole() {
	// 1. 콘솔 크기 설정 (기존 250보다 훨씬 안정적인 크기)
	system("mode con: cols=150 lines=45");

	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;

	// 2. 퀵에디트 모드 및 마우스 입력 방지
	GetConsoleMode(hInput, &mode);
	SetConsoleMode(hInput, mode & ~ENABLE_QUICK_EDIT_MODE & ~ENABLE_MOUSE_INPUT);

	// 3. 커서 숨기기 및 창 크기 고정 (X 버튼 활성화 유지)
	hideCursor();
	HWND hwnd = GetConsoleWindow();
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

int main() {
	initConsole(); // 모든 설정 통합 실행

	scene1();
	scene2();
	scene3();
	scene6();

	system("cls");
	goToXY(0, 0);
	cout << "모험이 끝났습니다. 게임을 종료하려면 아무 키나 누르세요...";
	system("pause > nul");
	return 0;
}
