#pragma once
#include<string>

#pragma once
#include <string>
#include <iostream>

class Poketmon {
private:
    std::string name;
    int level;
    int hp;
    int power;
    int baseHP;
    int basePower;

public:
    Poketmon(const std::string& n, int l, int h, int p);
    std::string GetName() const;
    int GetLevel() const;
    int GetHP() const;
    int GetPower() const;
    void SetLevel(int l);
    void ShowInfo() const;
};

여기서 정리 해볼게여
한번 이거 전투기획하는거 보고 코딩 시작해여 한번 기획 해볼게여
1. 플레이어가 야생 포켓몬을 조우한다.
2. 전투시스템 시작.

3. 스피드를 비교해서 스피드가 강한 포켓몬이 선턴 시작.

4. 선턴일 경우 선택지 (1. 공격, 2. 포션, 3. ....)
    일단 보시면 여기서 저희가 선택지를 뭐뭐할지 정해야 하구요
5. 턴을 종료후 효과에 따라 스텟에 영향을 줌.
    여기는 위에 선택지 기반으로 그대로 하면 대여

6. 상대턴 시작.

7. 반복
8. 쓰러트림.

어때여? 죠습니다
그러면 우선 저희 정하고 가져. 선택지 어디까지 넣어볼까요? 일단은 공격만 하는걸로 해보는거 어때여? 넹넹 천천히 추가하면되니깐 

그러면 cout으로 보여줍시다.

std::cout<<"야생의 골덕을 만났다!"<<std::endl;


