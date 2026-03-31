#include "Common.h"
#include "PokemonCore.h"
#include "PokemonData.h"

void fadeOut(int lines, int cols) {
	for (int i = 0; i < lines; i++) { goToXY(0, i); for (int j = 0; j < cols; j++) cout << " "; Sleep(5); }
	system("cls");
}

void drawFrame(const vector<wstring>& frame, int x, int y) {
	for (int i = 0; i < (int)frame.size(); i++) { goToXY(x, y + i); wcout << frame[i]; }
}

void scene1() {
	hideCursor(); fflush(stdout); (void)_setmode(_fileno(stdout), _O_U16TEXT); setFontSize(30);
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
	system("pause > nul"); int w, h; getActualSize(w, h); fflush(stdout); (void)_setmode(_fileno(stdout), _O_TEXT); fadeOut(h, w);
}

void scene2() {
	system("cls"); int w, h; getActualSize(w, h);
	int midX = w / 2 - 20, midY = h / 2 - 5;
	goToXY(midX, midY); cout << "========================================";
	goToXY(midX, midY + 1); cout << "           [ 당신의 이름은? ]           ";
	goToXY(midX + 5, midY + 4); cout << " 입력: "; cin >> g_playerName; g_player.playername = g_playerName;
	talk("오박사", g_playerName + "군 왔는가? 스타팅 포켓몬을 골라보렴!");
	cout << "1.파이리 2.꼬부기 3.이상해씨: "; int c; cin >> c;
	if (c == 1) { g_player.AddPokemon(make_unique<Charmander>(&g_player)); g_starterName = "파이리"; }
	else if (c == 2) { g_player.AddPokemon(make_unique<Squirtle>(&g_player)); g_starterName = "꼬부기"; }
	else { g_player.AddPokemon(make_unique<Bulbasaur>(&g_player)); g_starterName = "이상해씨"; }
	talk("오박사", "여행이 시작되었습니다!"); Sleep(1000);
}

void scene3() {
	fflush(stdout); (void)_setmode(_fileno(stdout), _O_U16TEXT); int w, h; getActualSize(w, h);
	vector<vector<wstring>> frames = { {L"  /\\  ", L" |__| "}, {L"   /\\   ", L"  |[]|  ", L" |____| "}, {L"    /\\    ", L"   |  |   ", L"   |[입]|  ", L"  |______| "} };
	for (auto& f : frames) { system("cls"); drawFrame(f, w / 2 - 5, h / 2 - 5); Sleep(700); }
	fflush(stdout); (void)_setmode(_fileno(stdout), _O_TEXT); talk("나", "여기가 '포켓몬 탑'인가.");
}

void renderBattleFrame(Pokemon& p, Pokemon& e, string msg, int mode) {
	fflush(stdout); (void)_setmode(_fileno(stdout), _O_U16TEXT); system("cls");
	wcout << L"\n  " << s2ws_battle(e.name) << L" HP: " << (int)e.hp << L"/" << (int)e.maxhp << endl;
	wcout << L"\n\n          [ 적 포켓몬 UI ]\n\n" << endl;
	wcout << L"  " << s2ws_battle(p.name) << L" HP: " << (int)p.hp << L"/" << (int)p.maxhp << endl;
	wcout << L"  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
	if (mode == 0) { goToXY(4, 18); wcout << s2ws_battle(msg); goToXY(50, 18); wcout << L"1.싸운다 4.도망"; }
	fflush(stdout); (void)_setmode(_fileno(stdout), _O_TEXT);
}

void scene4() {
	auto enemy = spawnEnemy(g_currentFloor); Pokemon* player = g_player.getLeadPokemon();
	while (player->hp > 0 && enemy->hp > 0) {
		renderBattleFrame(*player, *enemy, "무엇을 할까?", 0);
		int c; cin >> c; if (c == 4) break;
		enemy->hp -= player->attack / 2.0f; talk(player->name, "의 공격!");
		if (enemy->hp > 0) { player->hp -= enemy->attack / 3.0f; talk(enemy->name, "의 반격!"); }
	}
	if (enemy->hp <= 0) { talk("승리", "경험치를 얻었다!"); g_player.setexp(enemy->getFinalExp()); }
}

void scene5() {
	system("cls"); int w, h; getActualSize(w, h); int midX = w / 2 - 30;
	goToXY(midX, 3); cout << "======= [ SHOP ] GOLD: " << g_player.money << " G =======";
	goToXY(midX + 2, 6); cout << "1. Rare Candy (500G)  0. Exit Shop";
	int c; cin >> c; if (c == 1) Item::RareCandy(g_player);
}

void scene6() { talk("오박사", "축하하네! 진정한 마스터가 되었구먼!"); Sleep(3000); }

void sceneLoop() {
	while (g_currentFloor <= 10 && !g_player.isAllFainted()) {
		scene4(); if (g_player.isAllFainted()) break;
		scene5(); g_currentFloor++;
	}
}
