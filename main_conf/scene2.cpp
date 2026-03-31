#include <iostream>
#include <string>
#include <conio.h> 
#include <windows.h>
#include "Player.h"

using namespace std;

extern void setFontSize(int size);
extern void goToXY(int x, int y);
extern void getActualSize(int& width, int& height);
extern Player* player;

void talk(string name, string text) {
	int w, h;
	getActualSize(w, h);
	int baseY = h - 8;

	system("cls");
	// 1. 구분선
	goToXY(0, baseY);
	for (int i = 0; i < w - 1; i++) cout << "-";

	// 2. 이름 출력
	goToXY(10, baseY + 2);
	cout << "[" << name << "]: ";

	// [중요] 이전 입력(엔터 등)이 버퍼에 남아있으면 미리 비워줌
	while (_kbhit()) _getch();

	bool skip = false;

	// 3. 출력 루프 (한글 2바이트 처리 포함)
	for (int i = 0; i < (int)text.length(); i++) {
		// 출력 중 아무 키나 누르면 스킵 모드 활성화
		if (!skip && _kbhit()) {
			skip = true;
			while (_kbhit()) _getch(); // 눌린 키를 비움
		}

		// 한글(2바이트) 체크 및 출력
		if (text[i] & 0x80) { // 한글인 경우 (MSVC/CP949 기준)
			cout << text[i] << text[i + 1];
			i++;
		}
		else {
			cout << text[i];
		}

		if (!skip) Sleep(25); // 스킵이 아닐 때만 딜레이
	}

	// 4. 안내 문구
	goToXY(w - 25, h - 2);
	cout << "Next [Enter] ▼";

	// 문장이 다 나온 후, 다음 대사로 넘어가기 위한 엔터 대기
	while (_kbhit()) _getch(); // 남은 키 입력 제거
	system("pause > nul");
}

void scene2() {
	Sleep(500);
	setFontSize(24);
	system("cls");
	int w, h;
	getActualSize(w, h);

	int midX = (w / 2) - 20;
	int midY = (h / 2);
	goToXY(midX, midY - 2); cout << "========================================";
	goToXY(midX, midY - 1); cout << "           [ 당신의 이름은? ]           ";
	goToXY(midX, midY);     cout << "========================================";
	goToXY(midX + 5, midY + 2); cout << " 입력: ";

	//입력한 이름으로 플레이어 객체를 생성
	string inputname;
	cin >> inputname;
	player = new Player(inputname);

	// [핵심] 이름 입력 후 남은 '엔터' 기록을 무시하도록 버퍼 청소
	cin.ignore(1000, '\n');

	talk("오박사", inputname + "군 왔는가?");
	talk("오박사", "오늘은 자네가 이 포켓몬 탑에 처음 들어가보는 날이 아닌가!");
	talk("오박사", "아주 경사스러운 날이지!");
	talk("오박사", "자네는 마침 운이 정말 좋아. 원래라면 자네보다 먼저왔을 내 아들이 하루 늦어진다지 뭔가!");
	talk("오박사", "덕분에 아무래도 자네는 이 세 포켓몬중 원하는 아이를 파트너로 삼을 수 있겠군!");

	bool selectionDone = false;
	while (!selectionDone) {
		system("cls");
		getActualSize(w, h);
		midX = (w / 2) - 25;
		midY = (h / 2);
		goToXY(midX, midY - 4); cout << "==================================================";
		goToXY(midX, midY - 3); cout << " [오박사: 자, 이 테이블 위에 있는 3마리 중 하나를 고르렴!] ";
		goToXY(midX, midY - 2); cout << "==================================================";
		goToXY(midX, midY);     cout << " 1. 파이리(불)  2. 꼬부기(물)  3. 이상해씨(풀)";
		goToXY(midX, midY + 1); cout << "--------------------------------------------------";
		goToXY(midX + 20, midY + 3); cout << " 선택: ";

		int choice;
		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		cin.ignore(1000, '\n'); // 입력 후 버퍼 비우기
		// choice에 따라 포켓몬을 mypokemon 벡터에 추가
		if (choice == 1)
		{
			player->AddPokemon(make_unique<Charmander>(player));
			talk("오박사", "Charmander는 정말 탁월한 선택일세!");
		}
		else if (choice == 2)
		{
			player->AddPokemon(make_unique<Squirtle>(player));
			talk("오박사", "Squirtle는 정말 탁월한 선택일세!");
		}
		else if (choice == 3)
		{
			player->AddPokemon(make_unique<Bulbasaur>(player));
			talk("오박사", "Bulbasaur는 정말 탁월한 선택일세!");
		}
		else { talk("오박사", "허허, 장난치지 말고 하나를 골라보려무나."); continue; }
		selectionDone = true;
	}

	talk("오박사", "..음?");
	talk("오박사", "허허 어디서 들어왔는진 몰라도 자네, 이 친구도 데려가는 건 어떤가?");
	talk("오박사", "좋군! 연구실에 모르는 포켓몬을 두고 있을 순 없어서 말이야.");
	talk("오박사", "정없이 내쫓는 것 보단 자네를 따라가는게 나을거야.");
	talk("오박사", "한번 원없이 세상을 둘러보고 오게. 넓은 세상이 자네를 기다리고 있어.");
	talk("오박사", "그럼, 즐거운 여행을 시작하게나!");

	system("cls");
	goToXY(w / 2 - 12, h / 2);
	cout << "      여행이 시작되었습니다!       ";
	system("pause > nul");
}
