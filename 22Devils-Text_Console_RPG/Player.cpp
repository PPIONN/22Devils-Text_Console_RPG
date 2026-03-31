//Player.cpp

#include "Player.h"
#include <cmath>
#include <iostream>
#include <synchapi.h>

// 생성자/소멸자
Player::Player(std::string playername) : playername(playername)
{
	playerlevel = 1;
	playerexp = 0;
	money = 1000;
	setStatus(StatType::MaxEXP, 0);
}
Player::~Player()
{

}

// 레벨업 했을 때 초과 경험치를 넘겨주고 전체 능력치 재설정하는 함수
void Player::LevelUP()
{
	if (playerlevel >= maxlevel) // 만렙부터는 레벨업 불가. 경험치만 초기화
	{
		playerexp = 0;
	}
	else
	{
		while (playerexp >= playermaxexp) // 한 번에 레벨이 2 이상 오를 경우를 체크하기 위한 반복문
		{
			playerexp -= playermaxexp;
			++playerlevel;
			setStatus(StatType::MaxEXP, 0);

			for (auto& p : mypokemon)
			{
				if (p)
				{
					p->levelup();
				}
			}

			if (playerlevel >= maxlevel) // 레벨업했을 때 만렙이 될 경우 현재 경험치 0으로 초기화 후 반복문 종료
			{
				playerexp = 0;
				break;
			}
		}
	}
}

// 통합 setter
void Player::setStatus(StatType type, int amount)
{
	switch (type)
	{
	case StatType::EXP:
		if (playerlevel < maxlevel)
		{
			playerexp += amount;
			LevelUP(); // 경험치 얻은 뒤 레벨업이 가능해지면 바로 레벨업할 수 있게 설정
		}
		else
		{
			playerexp = 0; // 만렙에서 추가 경험치 획득을 방지
		}
		break;
	case StatType::Money:
		money += amount;
		break;
	case StatType::MaxEXP:
		if (playerlevel <= maxlevel)
		{
			float nexttotalexp = static_cast<float>(4.0f * pow(playerlevel + 1, 3) / 5.0f);
			float  currenttotalexp = static_cast<float>(4.0f * pow(playerlevel, 3) / 5.0f);
			playermaxexp = nexttotalexp - currenttotalexp;
		}
	default:
		break;
	}
}
int Player::setexp(int amount)
{
	playerexp += amount;
	return playerexp;
}
int Player::setmoney(int amount)
{
	money += amount;
	return money;
}
//통합 getter
int Player::getStatus(StatType type) const
{
	switch (type)
	{
	case StatType::EXP:
		return playerexp;
	case StatType::MaxEXP:
		return playermaxexp;
	case StatType::Level:
		return playerlevel;
	case StatType::Money:
		return money;
	default:
		break;
	}
}
int Player::getexp() const
{
	return playerexp;
}
int Player::getmoney() const
{
	return money;
}
// 인덱스 번호를 넣으면 해당 포켓몬의 포인터를 반환하는 함수
pokemon* Player::getPokemon(int index)
{
	// 잘못된 번호를 입력했을 때 프로그램이 터지는 것을 방지 (안전장치)
	if (index >= 0 && index < mypokemon.size())
	{
		return mypokemon[index].get();
	}
	return nullptr; // 잘못된 인덱스면 빈 포인터 반환
}
// 현재 보유 중인 포켓몬 수를 반환하는 함수 (UI 예외 처리에 유용함)
int Player::getPokemonCount() const
{
	return mypokemon.size();
}
// 능력치/소지금 확인
void Player::ShowStatus() //const
{
	std::cout << "Current Status" << std::endl;
	std::cout << "Player Name : " << playername << std::endl;
	std::cout << "Money : " << money << std::endl;
	std::cout << "Level : " << playerlevel << std::endl;
	std::cout << "EXP : " << playerexp << "/" << playermaxexp << std::endl;
	std::cout << "Quit Menu" << std::endl;
	// 인벤토리 들어가는 메뉴 없어서 임시로 여기에 통합해둠
	std::cout << "인벤내용" << std::endl;
	InventoryUI();
}


//아이템 관련 코드들

//오채율 - AddItem 함수 정의 추가
void Player::AddItem(const std::string& itemName)
{
	inventory.push_back(itemName);
	std::cout << itemName << "added to inventory!" << std::endl;
}

bool Player::HasItem(const std::string& itemName)
{
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] == itemName) return true;
	}
	return false;
}

void Player::RemoveItem(const std::string& itemName)
{
	for (auto it = inventory.begin(); it != inventory.end(); ++it)
	{
		if (*it == itemName)
		{
			inventory.erase(it);
			return;
		}
	}
}

void Player::PrintAllItems() const
{
	for (int i = 0; i < inventory.size(); i++) {
		std::cout << i + 1 << "." << "Item : " << inventory[i] << std::endl;  // ✅
	}
}

// 인벤토리 메뉴로 들어가서 전체 아이템을 표시하고, 아이템을 골라서 사용하거나 버리게 하는 코드
void Player::InventoryUI()
{
	int i = 0;
	// item 관련 코드 enum class로 변경하기 전까지 사용할 임시 코드
	Itemname selected;
	if (i == 0)
	{
		selected = Itemname::Null;
	}
	else {
		selected = ChangeItemEnum(inventory[i - 1]);
	}
	// item 관련 코드 enum class로 변경하기 전까지 사용할 임시 코드

	while (true)
	{
		PrintAllItems();
		std::cout << inventory.size() + 1 << "." << "Quit Menu" << std::endl;
		std::cout << "Select : ";
		if (std::cin >> i)
		{
			if (i == inventory.size() + 1 || inventory.size() == 0)
			{
				break;
			}
			else if (i <= inventory.size())
			{
				selected = ChangeItemEnum(inventory[i - 1]);
				while (true)
				{
					int c = 0;
					std::cout << "1. Use" << std::endl;
					std::cout << "2. Drop" << std::endl;
					std::cout << "3. Cancle" << std::endl;
					std::cout << "Select : ";
					std::cin >> c;
					if (c == 1)
					{
						ItemUse(selected);
						break;
					}
					else if (c == 2)
					{
						RemoveItem(inventory[i - 1]);
						break;
					}
					else if (c == 3)
					{
						break;
					}
					else
					{
						std::cout << "Wrong Input" << std::endl;
						std::cin.clear();
						std::cin.ignore();
					}
				}
			}
			else
			{
				std::cout << "Wrong Input" << std::endl;
				std::cin.clear();
				std::cin.ignore();
			}
		}
	}
}

// 아이템명 string이라 통합 Use 함수 쓰려고 Enum 형식으로 변경하는 함수
Itemname Player::ChangeItemEnum(const std::string& itemName)
{
	if (itemName == "RareCandy")
	{
		return Itemname::RareCandy;
	}
	else if (itemName == "HPPotion")
	{
		return Itemname::HPPotion;
	}
	else if (itemName == "FHPPotion")
	{
		return Itemname::FHPPotion;
	}
	else if (itemName == "MultiLens")
	{
		return Itemname::MultiLens;
	}
	else if (itemName == "PowerPorion")
	{
		return Itemname::PowerPorion;
	}
	else if (itemName == "randomexp")
	{
		return Itemname::randomexp;
	}
	else if (itemName == "randomgold")
	{
		return Itemname::randomgold;
	}
	else
	{
		return Itemname::Null;
	}
}

// Enum Class를 사용한 통합 Use 함수
void Player::ItemUse(Itemname item)
{
	Item foruse;	// 아이템 클래스가 static이 아니라서 임시로 객체 생성

	switch (item)
	{
	case Itemname::RareCandy:
		foruse.RareCandy(*this);
		break;
	case Itemname::HPPotion:
		foruse.UseHPPotion(*this);
		break;
	case Itemname::FHPPotion:
		foruse.UseFHPPotion(*this);
		break;
	case Itemname::MultiLens:
		foruse.UseMultiLens(*this);
		break;
	case Itemname::PowerPorion:
		foruse.UsePowerPotion(*this);
		break;
	case Itemname::randomexp:
		foruse.Userandomexp(*this);
		break;
	case Itemname::randomgold:
		foruse.Userandomgold(*this);
		break;
	default:
		std::cout << "Invaild Item" << std::endl;
		break;
	}
}



// 보유 포켓몬 관련 함수. 현재 플레이어가 포켓몬에게 포함된 protected 변수를 읽어올 수가 없어서 해당되는 getter 함수가 없는 부분은 비워둠

// 스타팅 포켓몬 선택
void Player::Selector()
{
	int Num;
	bool selected = false;

	while (selected == false)
	{
		std::unique_ptr<pokemon> newpokemon = nullptr;

		std::cout << "Character list" << std::endl;
		std::cout << "1. Charmander" << std::endl;
		std::cout << "2. Squirtle" << std::endl;
		std::cout << "3. Bulbasaur" << std::endl;
		std::cout << "4. Pikachu" << std::endl;
		std::cout << "Choose your character: ";
		std::cin >> Num;
		switch (Num)
		{
		case 1:
			newpokemon = std::make_unique<Charmander>(this);
			AddPokemon(std::move(newpokemon));
			selected = true;
			break;
		case 2:
			newpokemon = std::make_unique<Squirtle>(this);
			AddPokemon(std::move(newpokemon));
			selected = true;
			break;
		case 3:
			newpokemon = std::make_unique<Bulbasaur>(this);
			AddPokemon(std::move(newpokemon));
			selected = true;
			break;
		default:
			std::cout << "Invalid Input. Try Again." << std::endl;
			break;
		}
	}
}

// 새로운 포켓몬 추가. 획득할 때 매개변수랑 같은 양식으로 가져올 포켓몬을 std::move 쳐주면 됨.
void Player::AddPokemon(std::unique_ptr<pokemon> newpokemon)
{
	if (newpokemon != nullptr)
	{
		mypokemon.push_back(std::move(newpokemon));
	}
}

// 생사감별기
bool Player::isAllFainted() const
{
	// 보유 포켓몬이 아예 없는 경우(버그 상황) 전멸로 판정
	if (mypokemon.empty())
	{
		return true;
	}

	for (const auto& p : mypokemon)
	{
		// 하나라도 살아있는 포켓몬이 있다면 false
		if (p && p->gethp() > 0) {
			return false;
		}
	}
	return true;
}

// 포켓몬 리스트를 펼쳐주는 함수
void Player::MyPokemonUI()
{
	int i = 0;
	for (int i = 0; i < mypokemon.size(); ++i)
	{
		std::cout << i + 1 << "." << "Name : ";
		mypokemon[i]->ShowInfo(); // 함수에 포켓몬 이름이랑 종류 없어서 못읽어옴
		std::cout << std::endl;
	}
}

//배틀 시 선두 포켓몬 출전
pokemon* Player::getLeadPokemon()
{
	return mypokemon.empty() ? nullptr : mypokemon[0].get();
}

void Player::selectPokemon(bool IsBattle)
{
	int si;
	while (true)
	{
		system("cls");
		MyPokemonUI(); // 현재 보유 포켓몬 리스트 출력

		std::cout << "\n포켓몬 번호를 선택하세요 (0: 돌아가기): ";
		if (!(std::cin >> si)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			continue;
		}

		if (si == 0) break;
		if (si < 1 || si > mypokemon.size()) {
			std::cout << "잘못된 번호입니다." << std::endl;
			Sleep(500);
			continue;
		}

		// --- 메뉴 동적 생성 구간 ---
		std::vector<std::string> menuOptions;
		if (IsBattle)
		{
			menuOptions.push_back("교체 (Change)");
		}
		menuOptions.push_back("아이템 사용 (Item)");
		if (!IsBattle)
		{
			menuOptions.push_back("놓아주기 (Release)");
		}
		menuOptions.push_back("취소 (Cancel)");

		int a = 0;
		std::cout << "\n[ " << mypokemon[si - 1]->getname() << " 선택됨 ]" << std::endl;

		// 메뉴를 1번부터 순서대로 출력
		for (int i = 0; i < menuOptions.size(); ++i) {
			std::cout << (i + 1) << ". " << menuOptions[i] << std::endl;
		}

		std::cout << "선택: ";
		std::cin >> a;

		// 선택한 번호의 메뉴 텍스트를 가져옴
		if (a < 1 || a > menuOptions.size()) {
			std::cout << "잘못된 선택입니다." << std::endl;
			Sleep(500);
			continue;
		}

		std::string selectedMenu = menuOptions[a - 1];

		// --- 메뉴 텍스트 기반 기능 실행 ---
		if (selectedMenu == "교체 (Change)") {
			changePokemon();
			return;
		}
		else if (selectedMenu == "아이템 사용 (Item)") {
			InventoryUI();
			// 아이템 사용 후 보통은 해당 포켓몬에게 적용되므로 리스트로 돌아감
		}
		else if (selectedMenu == "놓아주기 (Release)") {
			if (mypokemon.size() > 1) {
				std::cout << mypokemon[si - 1]->getname() << "을(를) 보냈습니다." << std::endl;
				mypokemon.erase(mypokemon.begin() + si - 1);
				Sleep(1000);
				return;
			}
			else {
				std::cout << "마지막 포켓몬은 놓아줄 수 없습니다!" << std::endl;
				Sleep(1000);
			}
		}
		else if (selectedMenu == "취소 (Cancel)") {
			return;
		}
	}
}

pokemon* Player::changePokemon()
{
	system("cls");
	MyPokemonUI(); // 목록 보여주기

	int choice;
	std::cout << "\n교체할 포켓몬의 번호를 선택하세요 (0: 취소): ";
	if (!(std::cin >> choice) || choice == 0) return nullptr;

	if (choice < 1 || choice > mypokemon.size()) {
		std::cout << "잘못된 선택입니다." << std::endl;
		return nullptr;
	}

	// 기절한 포켓몬은 내보낼 수 없음
	if (mypokemon[choice - 1]->gethp() <= 0) {
		std::cout << mypokemon[choice - 1]->getname() << "은(는) 이미 기절해서 싸울 수 없다!" << std::endl;
		Sleep(1000);
		return nullptr;
	}

	// 선택한 포켓몬을 리스트의 맨 앞(0번)으로 보내서 선두로 설정
	std::swap(mypokemon[0], mypokemon[choice - 1]);

	std::cout << "가라! " << mypokemon[0]->getname() << "!" << std::endl;
	Sleep(1000);

	return mypokemon[0].get(); // 새로 선두가 된 포켓몬의 주소 반환
}

// 스타팅 포켓몬 파일 내에 같이 정의
Charmander::Charmander(Player* player) : pokemon::pokemon() // 파이리
{
	owner = player;
	this->level = player->playerlevel;

	this->hpGrowth = ((2 * 39 + 100) / 100 + 10);
	this->attackGrowth = ((2 * 52) / 100 + 5);
	this->defenseGrowth = ((2 * 43) / 100 + 5);
	this->specialAttackGrowth = ((2 * 60) / 100 + 5);
	this->specialDefenseGrowth = ((2 * 50) / 100 + 5);
	this->speedGrowth = ((2 * 65) / 100 + 5);

	this->levelhp(level);
	this->maxhp = hp;
	this->levelattack(level);
	this->leveldefense(level);
	this->levelspecialAttack(level);
	this->levelspecialDefense(level);
	this->levelspeed(level);

	this->type = { "Fire" };
	this->learnableSkills =
	{
	{"Scratch", "Normal", "Physical", 40, 100, 35, 1},
	{"Growl", "Normal", "Status", 0, 100, 40, 1},
	{"Ember", "Fire", "Special", 40, 100, 25, 4},
	{"Smokescreen", "Normal", "Status", 0, 100, 20, 8},
	{"Dragon Breath", "Dragon", "Special", 60, 100, 20, 12},
	{"Fire Fang", "Fire", "Physical", 65, 95, 15, 17},
	{"Slash", "Normal", "Physical", 70, 100, 20, 20},
	{"Flamethrower", "Fire", "Special", 90, 100, 15, 24},
	{"Scary Face", "Normal", "Status", 0, 100, 10, 28},
	{"Fire Spin", "Fire", "Special", 35, 85, 15, 32},
	{"Inferno", "Fire", "Special", 100, 50, 5, 36},
	{"Flare Blitz", "Fire", "Physical", 120, 100, 15, 40}
	};
	this->newpokeSkills();
}

Squirtle::Squirtle(Player* player) : pokemon::pokemon() // 꼬부기
{
	owner = player;
	this->level = player->playerlevel;

	this->hpGrowth = ((2 * 39 + 100) / 100 + 10);
	this->attackGrowth = ((2 * 52) / 100 + 5);
	this->defenseGrowth = ((2 * 43) / 100 + 5);
	this->specialAttackGrowth = ((2 * 60) / 100 + 5);
	this->specialDefenseGrowth = ((2 * 50) / 100 + 5);
	this->speedGrowth = ((2 * 65) / 100 + 5);

	this->levelhp(level);
	this->maxhp = hp;
	this->levelattack(level);
	this->leveldefense(level);
	this->levelspecialAttack(level);
	this->levelspecialDefense(level);
	this->levelspeed(level);

	this->type = { "Water" };
	this->learnableSkills =
	{
	{"Tackle", "Normal", "Physical", 40, 100, 35, 1},
	{"Tail Whip", "Normal", "Status", 0, 100, 30, 1},
	{"Water Gun", "Water", "Special", 40, 100, 25, 3},
	{"Withdraw", "Water", "Status", 0, 100, 40, 6},
	{"Rapid Spin", "Normal", "Physical", 50, 100, 40, 9},
	{"Bite", "Dark", "Physical", 60, 100, 25, 12},
	{"Water Pulse", "Water", "Special", 60, 100, 20, 15},
	{"Protect", "Normal", "Status", 0, 100, 10, 18},
	{"Rain Dance", "Water", "Status", 0, 100, 5, 21},
	{"Aqua Tail", "Water", "Physical", 90, 90, 10, 24},
	{"Shell Smash", "Normal", "Status", 0, 100, 15, 27},
	{"Iron Defense", "Steel", "Status", 0, 100, 15, 30},
	{"Hydro Pump", "Water", "Special", 110, 80, 5, 33},
	{"Skull Bash", "Normal", "Physical", 130, 100, 10, 36} };
	this->newpokeSkills();
}

Bulbasaur::Bulbasaur(Player* player) : pokemon::pokemon() // 이상해씨
{
	owner = player;
	this->level = player->playerlevel;

	this->hpGrowth = ((2 * 39 + 100) / 100 + 10);
	this->attackGrowth = ((2 * 52) / 100 + 5);
	this->defenseGrowth = ((2 * 43) / 100 + 5);
	this->specialAttackGrowth = ((2 * 60) / 100 + 5);
	this->specialDefenseGrowth = ((2 * 50) / 100 + 5);
	this->speedGrowth = ((2 * 65) / 100 + 5);

	this->levelhp(level);
	this->maxhp = hp;
	this->levelattack(level);
	this->leveldefense(level);
	this->levelspecialAttack(level);
	this->levelspecialDefense(level);
	this->levelspeed(level);

	this->type = { "Grass" };
	this->learnableSkills =
	{
	{"Tackle", "Normal", "Physical", 40, 100, 35, 1},
	{"Growl", "Normal", "Status", 0, 100, 40, 1},
	{"Vine Whip", "Grass", "Physical", 45, 100, 25, 3},
	{"Growth", "Normal", "Status", 0, 100, 40, 6},
	{"Leech Seed", "Grass", "Status", 0, 90, 10, 9},
	{"Razor Leaf", "Grass", "Physical", 55, 95, 25, 12},
	{"Poison Powder", "Poison", "Status", 0, 75, 35, 15},
	{"Sleep Powder", "Grass", "Status", 0, 75, 15, 15},
	{"Seed Bomb", "Grass", "Physical", 80, 100, 15, 18},
	{"Take Down", "Normal", "Physical", 90, 85, 20, 21},
	{"Sweet Scent", "Normal", "Status", 0, 100, 20, 24},
	{"Synthesis", "Grass", "Status", 0, 100, 5, 27},
	{"Worry Seed", "Grass", "Status", 0, 100, 10, 30},
	{"Power Whip", "Grass", "Physical", 120, 85, 10, 33},
	{"Solar Beam", "Grass", "Special", 120, 100, 10, 36}
	};
	this->newpokeSkills();
}
