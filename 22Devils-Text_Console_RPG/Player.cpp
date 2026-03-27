#include "Player.h"
#include <cmath>
#include <iostream>

// 생성자/소멸자
Player::Player()
{
	level = 1;
	exp = 0;
	money = 0;
}
Player::~Player()
{

}
// 플레이어 포켓몬 선택
Player* Player::Selector()
{
	Player* player = nullptr;
	int Num;

	while (player == nullptr)
	{
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
			player = new Charmander();
			break;
		case 2:
			player = new Squirtle();
			break;
		case 3:
			player = new Bulbasaur();
			break;
		case 4:
			player = new Pikachu();
			break;
		default:
			std::cout << "Invalid Input. Try Again." << std::endl;
			break;
		}
	}
	return player;
}

// 레벨에 따라 변동하는 능력치 설정
void Player::setStatus(int level)
{
	setmaxhp(level);
	setattack(level);
	setdefense(level);
	setspecialAttack(level);
	setspecialDefense(level);
	setspeed(level);
	setmaxexp(level);
}
//계산식
void Player::setmaxhp(int level) // 최대 체력
{
	maxhp = (static_cast<float>((2 * basehp + 100)) / 100 + 10) * level;
}
void Player::setattack(int level) // 공격
{
	attack = (static_cast<float>((2 * baseattack)) / 100 + 5) * level;
}
void Player::setdefense(int level) // 방어
{
	defense = (static_cast<float>((2 * basedefense)) / 100 + 5) * level;
}
void Player::setspecialAttack(int level) // 특수공격
{
	specialAttack = (static_cast<float>((2 * basespecialAttack)) / 100 + 5) * level;
}
void Player::setspecialDefense(int level) // 특수방어
{
	specialDefense = (static_cast<float>((2 * basespecialDefense)) / 100 + 5) * level;
}
void Player::setspeed(int level) // 스피드
{
	speed = (static_cast<float>((2 * basespeed)) / 100 + 5) * level;
}
void Player::setmaxexp(int level) // 레벨업에 필요한 경험치
{
	if (level <= maxlevel)
	{
		float nexttotalexp = static_cast<float>(4.0f * pow(level + 1, 3) / 5.0f);
		float  currenttotalexp = static_cast<float>(4.0f * pow(level, 3) / 5.0f);
		maxexp = nexttotalexp - currenttotalexp;
	}
}

// 레벨과 무관하게 변동하는 능력치
void Player::setcurrenthp(int DeltaHp) // 현재 체력
{
	currenthp += DeltaHp;
	if (currenthp > maxhp)
	{
		currenthp = maxhp;
	}
	if (currenthp < 0)
	{
		currenthp = 0;
	}
	// 추후 hp가 0이 될 경우 바로 사망처리하기 위한 임시 코드
	/*
	if (currenthp = 0)
	{
		std::cout << "Game Over" << endl;
	}
	*/
}
void Player::setexp(int Deltaexp) // 현재 경험치
{
	if (level < maxlevel)
	{
		exp += Deltaexp;
		LevelUP(); // 경험치 얻은 뒤 레벨업이 가능해지면 바로 레벨업할 수 있게 설정
	}
	else
	{
		exp = 0; // 만렙에서 추가 경험치 획득을 방지
	}
}
void Player::setmoney(int Deltamoney) // 소지금
{
	int newmoney = money + Deltamoney;
	money = newmoney;
}

// 레벨업 했을 때 초과 경험치를 넘겨주고 전체 능력치 재설정하는 함수
void Player::LevelUP()
{
	if (level >= maxlevel) // 만렙부터는 레벨업 불가. 경험치만 초기화
	{
		exp = 0;
	}
	else
	{
		while (exp >= maxexp) // 한 번에 레벨이 2 이상 오를 경우를 체크하기 위한 반복문
		{
			exp -= maxexp;
			++level;
			setStatus(level);
			setcurrenthp(2);

			if (level >= maxlevel) // 레벨업했을 때 만렙이 될 경우 현재 경험치 0으로 초기화 후 반복문 종료
			{
				exp = 0;
				break;
			}
		}
	}
}

// 능력치/소지금 확인
void Player::ShowStatus() const
{
	std::cout << "Current Status" << std::endl;
	std::cout << "Pokemon : " << name << std::endl;
	std::cout << "Money : " << money << std::endl;
	std::cout << "Level : " << level << std::endl;
	std::cout << "EXP : " << exp << "/" << maxexp << std::endl;
	std::cout << "HP : " << currenthp << "/" << maxhp << std::endl;
	std::cout << "Attack : " << attack << std::endl;
	std::cout << "Defense : " << defense << std::endl;
	std::cout << "SpecialAttack : " << specialAttack << std::endl;
	std::cout << "SpecialDefense : " << specialDefense << std::endl;
	std::cout << "Speed : " << speed << std::endl;
	std::cout << "Quit Menu" << std::endl;
}
int Player::getmoney() const
{
	return money;
}

// 플레이어 행위 함수
void Player::Attack()
{
	std::cout << name << " attacked enemy." << std::endl;
}
int Player::Damage()
{

}

// 자식 클래스(플레이어 포켓몬)
Charmander::Charmander() : Player::Player() // 파이리
{
	name = "Charmander";
	basehp = 39;
	baseattack = 52;
	basedefense = 43;
	basespecialAttack = 60;
	basespecialDefense = 60;
	basespeed = 65;
	setStatus(1);
	currenthp = maxhp;
}

Squirtle::Squirtle() : Player::Player() // 꼬부기
{
	name = "Squirtle";
	basehp = 44;
	baseattack = 48;
	basedefense = 65;
	basespecialAttack = 50;
	basespecialDefense = 64;
	basespeed = 43;
	setStatus(1);
	currenthp = maxhp;
}

Bulbasaur::Bulbasaur() : Player::Player() // 이상해씨
{
	name = "Bulbasaur";
	basehp = 45;
	baseattack = 49;
	basedefense = 49;
	basespecialAttack = 65;
	basespecialDefense = 65;
	basespeed = 45;
	setStatus(1);
	currenthp = maxhp;
}

Pikachu::Pikachu() : Player::Player() // 피카츄
{
	name = "Pikachu";
	basehp = 35;
	baseattack = 55;
	basedefense = 40;
	basespecialAttack = 50;
	basespecialDefense = 50;
	basespeed = 90;
	setStatus(1);
	currenthp = maxhp;
}
