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
#include <string>
#include <random>
#include <ctime>

using namespace std;


int main() {
	// 1. 캐릭터 능력치 설정
	string PikachuName = "피카츄";
	int PikachuHP = 100;
	int PikachuAttack = 10;
	int PikachuSpeed = 90;

	string PsyduckName = "고라파덕";
	int PsyduckHP = 80;
	int PsyduckAttack = 7;
	int PsyduckSpeed = 85;

	string first, second;
	int* fHP = nullptr;
	int* sHP = nullptr;
	int fAtk = 0, sAtk = 0;

	// 2. 스피드 비교 및 선공 결정
	cout << "[전투 시작!]" << endl;
	cout << PikachuName << " (스피드:" << PikachuSpeed << ") vs " << PsyduckName << " (스피드:" << PsyduckSpeed << ")" << endl;

	if (PikachuSpeed > PsyduckSpeed) {
		cout << ">> " << PikachuName << "가 더 빠릅니다! 선공을 가져갑니다." << endl;
		first = PikachuName; fHP = &PikachuHP; fAtk = PikachuAttack;
		second = PsyduckName; sHP = &PsyduckHP; sAtk = PsyduckAttack;
	}
	else if (PikachuSpeed < PsyduckSpeed) {
		cout << ">> " << PsyduckName << "가 더 빠릅니다! 선공을 가져갑니다." << endl;
		first = PsyduckName; fHP = &PsyduckHP; fAtk = PsyduckAttack;
		second = PikachuName; sHP = &PikachuHP; sAtk = PikachuAttack;
	}
	else {
		// 스피드가 같을 경우 랜덤 결정
		mt19937 gen(static_cast<unsigned int>(time(nullptr)));
		uniform_int_distribution<int> dis(0, 1);
		if (dis(gen) == 0) {
			cout << ">> 운 좋게 " << PsyduckName << "가 먼저 공격합니다!" << endl;
			first = PsyduckName; fHP = &PsyduckHP; fAtk = PsyduckAttack;
			second = PikachuName; sHP = &PikachuHP; sAtk = PikachuAttack;
		}
		else {
			cout << ">> 운 좋게 " << PikachuName << "가 먼저 공격합니다!" << endl;
			first = PikachuName; fHP = &PikachuHP; fAtk = PikachuAttack;
			second = PsyduckName; sHP = &PsyduckHP; sAtk = PsyduckAttack;
		}
	}

	// 3. 전투 루프 (누구든 HP가 0이 될 때까지)
	while (PikachuHP > 0 && PsyduckHP > 0) {
		// --- 선공의 턴 ---
		cout << "\n[" << first << "의 턴!]" << endl;
		*sHP -= fAtk;
		if (*sHP < 0) *sHP = 0;
		cout << ">> " << second << "에게 " << fAtk << "의 데미지를 입혔다!" << endl;
		cout << ">> " << second << " 잔여 HP: " << *sHP << endl;

		if (*sHP <= 0) break;

		// --- 후공의 턴 ---
		cout << "\n[" << second << "의 턴!]" << endl;
		*fHP -= sAtk;
		if (*fHP < 0) *fHP = 0;
		cout << ">> " << first << "에게 " << sAtk << "의 데미지를 입혔다!" << endl;
		cout << ">> " << first << " 잔여 HP: " << *fHP << endl;
	}

	// 4. 전투 후 행동 선택지
	bool isDone = false;
	while (!isDone) {
		int choice = 0;
		cout << "\n[무엇을 할까?]" << endl;
		cout << "1. 기술(십만볼트)  2. 아이템(상처약)  3. 교체  4. 도망" << endl;
		cout << "선택: ";
		cin >> choice;

		switch (choice) {
		case 1: cout << ">> 기술 '십만볼트'를 선택했습니다!" << endl; isDone = true; break;
		case 2: cout << ">> 아이템 '상처약'을 선택했습니다!" << endl; isDone = true; break;
		case 3: cout << ">> 교체를 시도합니다!" << endl; isDone = true; break;
		case 4: cout << ">> 무사히 도망쳤습니다!" << endl; isDone = true; break;
		default: cout << ">> 잘못된 입력입니다. 다시 선택하세요." << endl; break;
		}
	}

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
