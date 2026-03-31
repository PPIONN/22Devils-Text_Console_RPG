#include "Common.h"
#include "PokemonCore.h"
#include "PokemonData.h"

string g_playerName = "플레이어"; string g_starterName = "꼬부기";
int g_currentFloor = 1; Player g_player("플레이어");

void goToXY(int x, int y) { HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); COORD p = { (SHORT)x, (SHORT)y }; SetConsoleCursorPosition(h, p); }
void getActualSize(int& w, int& h) { CONSOLE_SCREEN_BUFFER_INFO c; GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c); w = c.srWindow.Right - c.srWindow.Left + 1; h = c.srWindow.Bottom - c.srWindow.Top + 1; }
void setFontSize(int s) { CONSOLE_FONT_INFOEX f; f.cbSize = sizeof(f); f.dwFontSize.Y = (SHORT)s; wcscpy_s(f.FaceName, L"Consolas"); SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &f); }
void hideCursor() { CONSOLE_CURSOR_INFO ci = { 100, FALSE }; SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci); }
void initConsole() { setFontSize(24); hideCursor(); system("cls"); }

wstring s2ws_battle(const string& s) {
	int len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, NULL, 0);
	wstring r(len, 0); MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, &r[0], len);
	if (!r.empty() && r.back() == L'\0') r.pop_back(); return r;
}

void talk(string name, string text) {
	system("cls"); int w, h; getActualSize(w, h);
	int midY = h - 8; goToXY(5, midY); cout << "========================================";
	goToXY(7, midY + 2); cout << "[" << name << "]"; goToXY(7, midY + 4);
	bool skip = false;
	for (int i = 0; i < (int)text.length(); i++) {
		if (!skip && _kbhit()) { (void)_getch(); skip = true; }
		if (skip) { cout << text.substr(i); break; }
		if (text[i] & 0x80) { cout << text[i] << text[i + 1]; i++; }
		else cout << text[i];
		Sleep(20);
	}
	goToXY(w - 20, h - 2); cout << "▶ [Enter]"; while (true) { if (_kbhit() && _getch() == 13) break; }
}

Pokemon::Pokemon() : name(""), type(""), level(1), hp(0.0f), maxhp(0.0f), attack(0.0f), defense(0.0f),
specialAttack(0.0f), specialDefense(0.0f), speed(0.0f), hpGrowth(0.0f), attackGrowth(0.0f),
defenseGrowth(0.0f), specialAttackGrowth(0.0f), specialDefenseGrowth(0.0f), speedGrowth(0.0f),
warattack(0.0f), wardefense(0.0f), warspecialAttack(0.0f), warspecialDefense(0.0f), warspeed(0.0f), owner(nullptr) {
}
Pokemon::~Pokemon() {}
void Pokemon::newpokescale(int lv) { this->level = lv; levelhp(lv); this->maxhp = this->hp; attack += attackGrowth * lv; defense += defenseGrowth * lv; }
void Pokemon::levelup() {
	level++; hp += hpGrowth; maxhp += hpGrowth; cout << "\n" << name << " 레벨업! (Lv." << level << ")\n";
	for (auto it = learnableSkills.begin(); it != learnableSkills.end(); ) {
		if (it->level <= level) { if (currentSkills.size() < 4) currentSkills.push_back(*it); it = learnableSkills.erase(it); }
		else ++it;
	}
}
void Pokemon::newpokeSkills() {
	for (auto it = learnableSkills.begin(); it != learnableSkills.end(); ) {
		if (it->level <= level) { if (currentSkills.size() >= 4) currentSkills.erase(currentSkills.begin()); currentSkills.push_back(*it); it = learnableSkills.erase(it); }
		else ++it;
	}
}
void Pokemon::levelhp(int l) { hp += hpGrowth * l; }
void Pokemon::levelattack(int l) { attack += attackGrowth * l; }
void Pokemon::leveldefense(int l) { defense += defenseGrowth * l; }
void Pokemon::ShowInfo() { cout << name << " (Lv." << level << ") HP: " << (int)hp << "/" << (int)maxhp; }

Player::Player(string n) : playername(n), money(1000), playerlevel(1), playerexp(0), playermaxexp(100) {}
void Player::setStatus(StatType type, int amount) {
	if (type == StatType::MaxEXP) {
		float next = (float)(4.0 * pow((double)playerlevel + 1.0, 3.0) / 5.0);
		float curr = (float)(4.0 * pow((double)playerlevel, 3.0) / 5.0);
		playermaxexp = (int)(next - curr);
	}
	else if (type == StatType::Money) money += amount;
}
void Player::LevelUP() {
	while (playerexp >= playermaxexp) {
		playerexp -= playermaxexp; playerlevel++; setStatus(StatType::MaxEXP, 0);
		cout << "\n[레벨업] " << playername << " 레벨: " << playerlevel << endl;
		for (auto& p : mypokemon) p->levelup();
	}
}
int Player::setexp(int a) { playerexp += a; LevelUP(); return playerexp; }
int Player::setmoney(int a) { money += a; return money; }
void Player::AddPokemon(unique_ptr<Pokemon> p) { mypokemon.push_back(move(p)); }
bool Player::isAllFainted() const { for (auto& p : mypokemon) if (p->hp > 0) return false; return true; }
void Player::MyPokemonUI() { system("cls"); for (int i = 0; i < (int)mypokemon.size(); i++) { cout << i + 1 << ". "; mypokemon[i]->ShowInfo(); cout << endl; } }
Pokemon* Player::getLeadPokemon() { return mypokemon.empty() ? nullptr : mypokemon[0].get(); }

void Item::RareCandy(Player& p) { if (p.money >= 500) { p.money -= 500; p.getLeadPokemon()->levelup(); talk("시스템", "레벨업!"); } }
void Item::BuyHPPotion(Player& p) { if (p.money >= 100) { p.money -= 100; p.getLeadPokemon()->hp = min(p.getLeadPokemon()->maxhp, p.getLeadPokemon()->hp + 20.0f); talk("시스템", "회복!"); } }
void Item::BuyFHPPotion(Player& p) { if (p.money >= 100) { p.money -= 100; p.getLeadPokemon()->hp = p.getLeadPokemon()->maxhp; talk("시스템", "완전회복!"); } }
void Item::BuyPowerPotion(Player& p) { if (p.money >= 100) { p.money -= 100; p.getLeadPokemon()->attack += 20.0f; talk("시스템", "공격력 상승!"); } }
void Item::Buyrandomexp(Player& p) { p.money -= 100; }
void Item::Userandomexp(Player& p) { int e = rand() % 451 + 50; p.setexp(e); talk("시스템", to_string(e) + " 경험치 획득!"); }
void Item::Buyrandomgold(Player& p) { p.money -= 100; }
void Item::Userandomgold(Player& p) { int g = rand() % 451 + 50; p.setmoney(g); talk("시스템", to_string(g) + " 골드 획득!"); }
