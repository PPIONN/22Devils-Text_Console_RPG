#include "Player.h"

Player::Player()
{
	level = 1;
	exp = 0;
	setmaxexp(1);
}
Player::~Player()
{

}
Player* Player::Selector()
{
	Player* player = NULL;
	int Num;

	std::cout << "Character list" << std::endl;
	std::cout << "1. Charmander" << std::endl;
	std::cout << "2. Squirtle" << std::endl;
	std::cout << "3. Bulbasaur" << std::endl;
	std::cout << "4. Pikachu" << std::endl;
	std::cout << "Choose your character: ";
	std::cin >> Num;
	while (player == NULL)
	{
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
void Player::StatusGrowth(int level)
{
	sethp(level);
	setattack(level);
	setdefense(level);
	setspecialAttack(level);
	setspecialDefense(level);
	setspeed(level);
	setmaxexp(level);
}
void Player::setmaxhp(int level)
{
	maxhp = (static_cast<float>((2 * basehp + 100)) / 100) * level;
}
void Player::setcurrenthp(int DeltaHp)
{
	int newcurrenthp = currenthp + DeltaHp;
	currenthp = newcurrenthp;
}
void Player::setattack(int level)
{
	attack = (static_cast<float>((2 * baseattack)) / 100 + 5) * level;
}
void Player::setdefense(int level)
{
	defense = (static_cast<float>((2 * basedefense)) / 100 + 5) * level;
}
void Player::setspecialAttack(int level)
{
	specialAttack = (static_cast<float>((2 * basespecialAttack)) / 100 + 5) * level;
}
void Player::setspecialDefense(int level)
{
	specialDefense = (static_cast<float>((2 * basespecialDefense)) / 100 + 5) * level;
}
void Player::setspeed(int level)
{
	speed = (static_cast<float>((2 * basespeed)) / 100 + 5) * level;
}
void Player::setmaxexp(int level)
{
	maxexp = static_cast<float>(4 * pow(level, 3) / 5);
}
void Player::LevelUP()
{
	if (exp >= maxexp)
	{
		int newexp = exp - maxexp;
		++level;
		StatusGrowth(level);
		exp = newexp;
	}
}
void Player::ShowStatus() const
{
	std::cout << "Current Status" << std::endl;
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

Charmander::Charmander() : Player::Player()
{
	name = "Charmander";
	basehp = 39;
	baseattack = 52;
	basedefense = 43;
	basespecialAttack = 60;
	basespecialDefense = 60;
	basespeed = 65;
	maxhp = sethp(1);
	currenthp = maxhp;
	attack = setattack(1);
	defense = setdefense(1);
	specialAttack = setspecialAttack(1);
	specialDefense = setspecialDefense(1);
	speed = setspeed(1);
}

Squirtle::Squirtle() : Player::Player()
{
	name = "Squirtle";
	basehp = 44;
	baseattack = 48;
	basedefense = 65;
	basespecialAttack = 50;
	basespecialDefense = 64;
	basespeed = 43;
	maxhp = sethp(1);
	currenthp = maxhp;
	attack = setattack(1);
	defense = setdefense(1);
	specialAttack = setspecialAttack(1);
	specialDefense = setspecialDefense(1);
	speed = setspeed(1);
}

Bulbasaur::Bulbasaur() : Player::Player()
{
	name = "Bulbasaur";
	basehp = 45;
	baseattack = 49;
	basedefense = 49;
	basespecialAttack = 65;
	basespecialDefense = 65;
	basespeed = 45;
	maxhp = sethp(1);
	currenthp = maxhp;
	attack = setattack(1);
	defense = setdefense(1);
	specialAttack = setspecialAttack(1);
	specialDefense = setspecialDefense(1);
	speed = setspeed(1);
}

Pikachu::Pikachu() : Player::Player()
{
	name = "Pikachu";
	basehp = 35;
	baseattack = 55;
	basedefense = 40;
	basespecialAttack = 50;
	basespecialDefense = 50;
	basespeed = 90;
	maxhp = sethp(1);
	currenthp = maxhp;
	attack = setattack(1);
	defense = setdefense(1);
	specialAttack = setspecialAttack(1);
	specialDefense = setspecialDefense(1);
	speed = setspeed(1);
}
