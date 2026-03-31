#include "Common.h"
#include <io.h>
#include <fcntl.h>

void fadeOut(int lines, int cols) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < lines; i++) {
		SetConsoleCursorPosition(hConsole, { 0, (SHORT)i });
		for (int j = 0; j < cols; j++) wcout << L" ";
		Sleep(5);
	}
	system("cls");
}

void scene1() {
	hideCursor();

	// [수정] C6031 경고 해결: (void) 추가
	(void)_setmode(_fileno(stdout), _O_U16TEXT);
	setFontSize(30);

	wcout << LR"(
         ██████████████████████████████████████████████████████   █████████  █████████████████████████████████
                                        ██████████████████████████████████████████████████████   █████████  █████████████████████████████████
                                        ██████████████████████████████████████████████████████   █████████  █████████████████████████████████
                                        ██████████████████████████████████████████████████████   █████████  █████████████████████████████████
                                        ██████████████████████████████████████████████████████   █████████  █████████████████████████████████
                                        ██████████████████████████████████████████████████████

             Press any key to start!

                                                            조원: 오채율, 신건호, 이현준
                                                                  이채호, 배건우, 노용수 
    )" << endl;

	system("pause > nul");

	int currW, currH;
	getActualSize(currW, currH);
	fadeOut(currH, currW);

	// [수정] C6031 경고 해결: (void) 추가
	(void)_setmode(_fileno(stdout), _O_TEXT);
}
