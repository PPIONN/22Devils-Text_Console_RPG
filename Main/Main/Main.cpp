//스피드 비교, hp랑 공격력 적용해서 전투종료 (전투시스템 구현 완료/스텟 적용 전)
//몬스터 쓰러뜨릴시 얻을 골드, 경험치 구현필효
//몬스터 조우시 플레이어 레벨에 따라 몬스터 레벨,스텟 적용 구현 필요
//ex)스타팅 포켓몬 4마리중 한마리 결정하기 (건우님이랑 대화 필요)
//ex)1레벨로 시작해서 첫번째 상대 몬스터 조우
//    조우할 몬스터 랜덤으로 결정, 1레벨로 설정, 스텟 1레벨로 적용
//전투 시작시 선택지 (일단 기술 창만)
//선택지에서 기술 구현. 기술 창에 플레이어 포켓몬이 습득한 기술 나열(플레이어 포켓몬의 레벨에 따라 기술 획득)
//기술의 데미지를 플레이어 포켓몬의 스텟에 비례해서 적용
//데미지를 상대 포켓몬에 전달                                                                           (구현 완료)
//ex)쓰러뜨린후 해당 몬스터의 레벨에 따라 경험치, 골드 획득




//기술 
//아이템 x
//교체 x
//도망 x

//1. 스피드 비교후 선턴결정//2. 선택지 등장(1.기술 2. 아이템 ... etc)//3.턴 종료 후 효과 적용//4.상대턴 시작//반복

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
using namespace std;

int main() {

    //피카츄(플레이어) 스텟
    string PkachuName = "피카츄";
    int PikachuHP = 100;
    int PikachuAttack = 10;
    int PikachuSpeed = 90;

    //고라파덕(몬스터) 스텟
    string PsyduckName = "고라파덕";
    int PsyduckHP = 80;
    int PsyduckAttack = 7;
    int PsyduckSpeed = 85;
    
    string first, second; // 선공과 후공의 이름을 저장하는 변수
    int *fHP, *sHP;       // 선공과 후공의 현재 HP 주소를 가리키는 포인터 변수
    int fAtk, sAtk;       // 선공과 후공의 공격력 수치를 저장하는 변수

    // 1. 스피드 비교 후 선턴 결정 
    cout << "[BATTLE START]" << endl;
    cout << PkachuName << "의 스피드 : " << PikachuSpeed << " vs " << PsyduckName << "의 스피드 : "<< PsyduckSpeed << endl; 
 
    // 우선 대전 구현 아래 하는중인데 현재 우리팀 고라파덕 vs 상대팀 피카츄 이건 지금 거의 고정인데 <- (x) <- 상대방이 고라파덕이든 피카츄든 나올수있다 이렇게 만들면 된다는걸까요?
   


 

    if (PikachuSpeed > PsyduckSpeed) // 스피드 비교
    {
        //피카츄가 고라파덕보다 빠를때 피카츄 선턴
        cout << PkachuName <<" ( SPD:" << PikachuSpeed <<") vs"<< PsyduckName <<"(SPD: "<< PsyduckSpeed <<")" << endl;
        cout << ">> " << PkachuName <<"가 더 빠르므로 선공을 가져갑니다!" << endl;
        first = PkachuName; fHP = &PikachuHP; fAtk = PikachuAttack;
        second = PsyduckName; sHP = &PsyduckHP; sAtk = PsyduckAttack;
        
    }
    else if(PikachuSpeed < PsyduckSpeed){
        //고라파덕이 피카츄보다 빠를때 고라파덕 선턴
        cout << PsyduckName << " ( SPD:" << PsyduckSpeed << ") vs" << PsyduckName << "(SPD: " << PikachuSpeed << ")" << endl;
        cout << ">> " << PsyduckName << "가 더 빠르므로 선공을 가져갑니다!" << endl;
        first = PsyduckName; fHP = &PsyduckHP; fAtk = PsyduckAttack;
        second = PkachuName; sHP = &PikachuHP; sAtk = PikachuAttack;
    }
    else{
        // 1. 시드 설정: 현재 시간을 시드로 사용
        std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));

        // 2. 범위 설정: 0 또는 1 (0: 선공, 1: 후공)
        std::uniform_int_distribution<int> dis(0, 1);
        int result = dis(gen);
        if (result == 0) {
            std::cout << "당신이 [선공]입니다!" << std::endl; // 고라파덕선공
            first = PsyduckName; fHP = &PsyduckHP; fAtk = PsyduckAttack;
            second = PkachuName; sHP = &PikachuHP; sAtk = PikachuAttack;
        }
        else {
            std::cout << "당신은 [후공]입니다!" << std::endl; // 피카츄선공
            first = PkachuName; fHP = &PikachuHP; fAtk = PikachuAttack;
            second = PsyduckName; sHP = &PsyduckHP; sAtk = PsyduckAttack;
        }


    }


   // 2. 전투 루프 (HP가 0이 될 때까지 반복)
    while (PikachuHP > 0 && PsyduckHP > 0) {
        // --- 선공 턴 ---
        cout << "\n[" << first << "'s Turn]" << endl;
        cout << "1. Skill  2. Item  3. Switch  4. Run" << endl;
        cout << ">> " << first << " uses Attack!" << endl;
        
        //선턴자의 공격력 만큼 선턴자 hp 차감
        *sHP -= fAtk; // 상대 HP 차감
        if (*sHP < 0) *sHP = 0; // HP 0 이하 방지
        
        //>>(후턴자)took(선턴자의 공격력)damage!
        cout << ">> " << second << " took " << fAtk << " damage!" << endl;
        //>>(후턴자)hp:(후턴자hp)
        cout << ">> " << second << " HP: " << *sHP << endl;

        if (*sHP <= 0) break; // 상대가 쓰러지면 즉시 종료

        // --- 후공 턴 (상대 턴 시작) ---
        cout << "\n[" << second << "'s Turn]" << endl;
        cout << ">> " << second << " uses Counter-Attack!" << endl;
        
        //후턴자의 공격력 만큼  선턴자 hp 차감
        *fHP -= sAtk; 
        //선턴자의 체력이 0보다 작을경우 0으로
        if (*fHP < 0) *fHP = 0;

        cout << ">> " << first << " took " << sAtk << " damage!" << endl;
        cout << ">> " << first << " HP: " << *fHP << endl;
    }
    
    // 2. 선택지 등장
    bool B = false;
    while (B == false)
    {
        int A = 0;
        cout << "\n[무엇을 할까?]" << endl;
        cout << "1. 기술(십만볼트)  2. 아이템(상처약)  3. 교체  4. 도망" << endl;
        cin >> A;

        switch (A)
        {
        case 1:
            cout << ">> 기술 '십만볼트'를 선택했습니다!" << endl;
            B = true;
            break;
        case 2:
            cout << ">> 아이템 '상처약'을 선택했습니다!" << endl;
            B = true;
            break;
        case 3:
            cout << ">> 교체를 선택했습니다!" << endl;
            B = true;
            break;
        case 4:
            cout << ">> 도망을 선택했습니다!" << endl;
            B = true;
            break;
        default:
            cout << "잘못된 입력입니다. 다시 선택하세요." << endl;
            break;
        }

    }

    // 3. 턴 종료 후 효과 적용
    cout << "\n[효과 적용]" << endl;
    cout << "피카츄의 십만볼트! 효과가 굉장했다!" << endl;
    cout << "꼬부기 HP: 100 -> 20 (-80)" << endl;
    cout << "상대방의 마비 상태가 지속됩니다." << endl;

    // 4. 상대턴 시작
    cout << "\n[상대방의 턴]" << endl;
    cout << "꼬부기는 몸저누워 움직일 수 없다!" << endl;
    cout << "------------------------------" << endl;
    cout << "턴이 종료되었습니다. 다음 라운드로 넘어갑니다." << endl;

    return 0;
}

//그러면 스텟을 한번 불러와 볼까여 스텟선언 해볼까여 일단 간단하게

// 혹시 랜덤테스트 안에 들어있는게 플레이어인가요? 기존에 만들어둔것들 여기서 조립한다는 느낌이 좋을거같아서요  bbbbb
// 그거 봐도 어쩔수가 없는게 건우님이랑 채호님이랑 저희랑 다 달라서 쩔수입니다
// 제가 일단 저 코드짜는거에만 정신팔려서 팀원분들 코드를 유심히 안본게 큰듯해서;;

//그러면 지금 당장 호출해야하는 정보들 정리 해볼게여. 1. 공격력, 2. 생명력, 3. 스피드, 4. 레벨 아 이건 좀따할까k
// 혹시 랜덤테스트 안에 들어있는게 플레이어인가요? 기존에 만들어둔것들 여기서 조립한다는 느낌이 좋을거같아서요  bbbbb
// 그거 봐도 어쩔수가 없는게 건우님이랑 채호님이랑 저희랑 다 달라서 쩔수입니다
// 제가 일단 저 코드짜는거에만 정신팔려서 팀원분들 코드를 유심히 안본게 큰듯해서;;

//그러면 지금 당장 호출해야하는 정보들 정리 해볼게여. 1. 공격력, 2. 생명력, 3. 스피드, 4. 레벨 아 이건 좀따할까