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
void FHPPotion()
{

}

void MultiLens()
{
	//이건 시스템 쪽을 더 건드려봐야하지 않을까 싶음
	//공격선택지를 바로 누르게 하는 느낌
}
