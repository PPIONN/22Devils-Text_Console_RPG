//Item.cpp

#include <iostream>
#include "Item.h"

void Item::RareCandy()
{
	XP += 100;
	std::cout << "레벨이 " << Level << "로 올랐다!" << std::endl;

}
void Item::HPPotion()
{
	HP += 20 ;
}
void Item::FHPPotion()
{
	HP = MaxHP;
}

void Item::MultiLens()
{
   //전투 시스템 완성 후 연결 필요
   //예시)공격 시 hotCount를 1->2로 변경
}

void Item::Booster()
{


}


