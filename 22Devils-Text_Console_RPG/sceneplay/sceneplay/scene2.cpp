#include <iostream>
#include <string>
#include <conio.h> 
#include <windows.h>

using namespace std;

extern void setFontSize(int size);
extern void goToXY(int x, int y);
extern void getActualSize(int& width, int& height);
extern string g_playerName;
extern string g_starterName;

// 대사창 출력 함수 (안정성 강화)
void talk(string name, string text) {
	int w, h;
	getActualSize(w, h);
	int baseY = h - 10;

	system("cls");

	goToXY(5, baseY);
	for (int i = 0; i < w - 10; i++) cout << "=";

	goToXY(10, baseY + 2);
	cout << "[" << name << "]";
	goToXY(10, baseY + 4);

	while (_kbhit()) _getch();

	bool skip = false;
	for (int i = 0; i < (int)text.length(); i++) {
		if (!skip && _kbhit()) {
			skip = true;
			while (_kbhit()) _getch();
		}

		if (text[i] & 0x80) {
			cout << text[i] << text[i + 1];
			i++;
		}
		else {
			cout << text[i];
		}
		if (!skip) Sleep(20);
	}

	goToXY(w - 30, h - 3);
	cout << "▶ [Enter]를 누르세요";

	// 엔터 입력 대기
	while (true) {
		if (_kbhit()) {
			if (_getch() == 13) break;
		}
	}
}

void scene2() {
	Sleep(500);
	setFontSize(24);
	system("cls");
	int w, h;
	getActualSize(w, h);

	int midX = (w / 2) - 20;
	int midY = (h / 2) - 5;

	goToXY(midX, midY);     cout << "========================================";
	goToXY(midX, midY + 1); cout << "           [ 당신의 이름은? ]           ";
	goToXY(midX, midY + 2); cout << "========================================";
	goToXY(midX + 5, midY + 4); cout << " 입력: ";

	// [수정] string으로 제대로 입력받기
	string tempName;
	cin >> tempName;
	g_playerName = tempName;
	cin.ignore(1000, '\n'); // 남은 엔터 제거

	talk("오박사", g_playerName + "군 왔는가?");
	talk("오박사", "오늘은 자네가 이 포켓몬 탑에 처음 들어가보는 날이 아닌가!");
	talk("오박사", "아주 경사스러운 날이지!");
	talk("오박사", "자네는 마침 운이 정말 좋아. 원래라면 자네보다 먼저왔을 내 아들이 하루 늦어진다지 뭔가!");
	talk("오박사", "덕분에 아무래도 자네는 이 세 포켓몬중 원하는 아이를 파트너로 삼을 수 있겠군!");

	bool selectionDone = false;
	while (!selectionDone) {
		system("cls");
		getActualSize(w, h);
		midX = (w / 2) - 25;
		midY = (h / 2) - 5;

		goToXY(midX, midY);     cout << "==================================================";
		goToXY(midX, midY + 1); cout << " [오박사: 자, 이 세 마리 중 하나를 고르렴!] ";
		goToXY(midX, midY + 2); cout << "==================================================";
		goToXY(midX + 2, midY + 4); cout << " 1. 파이리(불)  2. 꼬부기(물)  3. 이상해씨(풀)";
		goToXY(midX, midY + 5);     cout << "--------------------------------------------------";
		goToXY(midX + 15, midY + 7); cout << " 선택 번호: ";

		int choice;
		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		cin.ignore(1000, '\n');

		if (choice == 1) g_starterName = "파이리";
		else if (choice == 2) g_starterName = "꼬부기";
		else if (choice == 3) g_starterName = "이상해씨";
		else {
			talk("오박사", "허허, 장난치지 말고 하나를 골라보려무나.");
			continue;
		}

		talk("오박사", g_starterName + "은(는) 정말 탁월한 선택일세!");
		selectionDone = true;
	}

	talk("오박사", "..음?");
	talk("오박사", "허허 어디서 들어왔는진 몰라도 자네, 이 친구도 데려가는 건 어떤가?");
	talk("오박사", "좋군! 연구실에 모르는 포켓몬을 두고 있을 순 없어서 말이야.");
	talk("오박사", "정없이 내쫓는 것 보단 자네를 따라가는게 나을거야.");
	talk("오박사", "한번 원없이 세상을 둘러보고 오게. 넓은 세상이 자네를 기다리고 있어.");
	talk("오박사", "그럼, 즐거운 여행을 시작하게나!");

	system("cls");
	getActualSize(w, h);
	goToXY(w / 2 - 15, h / 2);
	cout << "      여행이 시작되었습니다!       ";
	Sleep(2000);
}
