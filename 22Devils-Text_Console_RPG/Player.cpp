//Player.cpp

#include "Player.h"
#include <cmath>
#include <iostream>

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

void Player::selectPokemon()
{
	int si;
	bool IsBattle = false;
	MyPokemonUI();
	while (true)
	{
		if (!(std::cin >> si))
		{
			std::cout << "Error" << std::endl;

		}
		int a = 0;
		std::cout << "selected : " << mypokemon[si - 1] /*포켓몬 이름*/ << std::endl;
		std::cout << "What to do?" << std::endl;
		/*배틀 중일 때만*/
		std::cout << "1. Change this Pokemon" << std::endl;
		std::cout << "2. Use Item" << std::endl;
		/*비전투 때만*/
		std::cout << "3. Release this Pokemon" << std::endl;
		std::cout << "4. Cancel" << std::endl;
		std::cin >> a;
		switch (a)
		{
		case 1:
			if (IsBattle = true)
			{
				changePokemon();
			}
			else
			{
				std::cout << "Not in Battle" << std::endl;
			}
			break;
		case 2:
			InventoryUI();
			break;
		case 3:
			if (IsBattle = false)
			{
				mypokemon.erase(mypokemon.begin() + si - 1);
			}
			else
			{
				std::cout << "Cannot do that in Battle" << std::endl;
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Player::changePokemon()
{
	//미구현
}

// 스타팅 포켓몬 파일 내에 같이 정의. 기술은 아직 안바꿈
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
		{ "Hypnosis", "Psychic", "Status", 0, 60, 20, 0 },
		{ "Lick", "Ghost", "Physical", 20, 100, 30, 0 },
		{ "Spite", "Ghost", "Status", 0, 100, 10, 5 },
		{ "Mean Look", "Normal", "Status", 0, -1, 5, 8 },
		{ "Curse", "Unknown", "Status", 0, -1, 10, 12 },
		{ "Night Shade", "Ghost", "Special", 0, 100, 15, 15 },
		{ "Confuse Ray", "Ghost", "Status", 0, 100, 10, 19 },
		{ "Sucker Punch", "Dark", "Physical", 80, 100, 5, 22 },
		{ "Payback", "Dark", "Physical", 50, 100, 10, 26 },
		{ "Shadow Ball", "Ghost", "Special", 80, 100, 15, 29 },
		{ "Dream Eater", "Psychic", "Special", 100, 100, 15, 33 },
		{ "Dark Pulse", "Dark", "Special", 80, 100, 15, 36 },
		{ "Destiny Bond", "Ghost", "Status", 0, -1, 5, 40 },
		{ "Nightmare", "Ghost", "Status", 0, -1, 15, 43 }
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
		{ "Hypnosis", "Psychic", "Status", 0, 60, 20, 0 },
		{ "Lick", "Ghost", "Physical", 20, 100, 30, 0 },
		{ "Spite", "Ghost", "Status", 0, 100, 10, 5 },
		{ "Mean Look", "Normal", "Status", 0, -1, 5, 8 },
		{ "Curse", "Unknown", "Status", 0, -1, 10, 12 },
		{ "Night Shade", "Ghost", "Special", 0, 100, 15, 15 },
		{ "Confuse Ray", "Ghost", "Status", 0, 100, 10, 19 },
		{ "Sucker Punch", "Dark", "Physical", 80, 100, 5, 22 },
		{ "Payback", "Dark", "Physical", 50, 100, 10, 26 },
		{ "Shadow Ball", "Ghost", "Special", 80, 100, 15, 29 },
		{ "Dream Eater", "Psychic", "Special", 100, 100, 15, 33 },
		{ "Dark Pulse", "Dark", "Special", 80, 100, 15, 36 },
		{ "Destiny Bond", "Ghost", "Status", 0, -1, 5, 40 },
		{ "Nightmare", "Ghost", "Status", 0, -1, 15, 43 }
	};
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
		{ "Hypnosis", "Psychic", "Status", 0, 60, 20, 0 },
		{ "Lick", "Ghost", "Physical", 20, 100, 30, 0 },
		{ "Spite", "Ghost", "Status", 0, 100, 10, 5 },
		{ "Mean Look", "Normal", "Status", 0, -1, 5, 8 },
		{ "Curse", "Unknown", "Status", 0, -1, 10, 12 },
		{ "Night Shade", "Ghost", "Special", 0, 100, 15, 15 },
		{ "Confuse Ray", "Ghost", "Status", 0, 100, 10, 19 },
		{ "Sucker Punch", "Dark", "Physical", 80, 100, 5, 22 },
		{ "Payback", "Dark", "Physical", 50, 100, 10, 26 },
		{ "Shadow Ball", "Ghost", "Special", 80, 100, 15, 29 },
		{ "Dream Eater", "Psychic", "Special", 100, 100, 15, 33 },
		{ "Dark Pulse", "Dark", "Special", 80, 100, 15, 36 },
		{ "Destiny Bond", "Ghost", "Status", 0, -1, 5, 40 },
		{ "Nightmare", "Ghost", "Status", 0, -1, 15, 43 }
	};
	this->newpokeSkills();
}
