#include "Common.h"
#include <ctime>

int main() {
	srand((unsigned int)time(NULL));
	initConsole();
	scene1();
	scene2();
	scene3();
	sceneLoop();
	scene6();
	return 0;
}
