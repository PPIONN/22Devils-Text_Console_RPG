#include "Common.h"
#include "GameData.h"

// Data.cpp에 있는 플레이어 객체를 사용합니다.
extern Player g_player;

void scene5() {
	int w, h;
	getActualSize(w, h);
	bool inShop = true;

	while (inShop) {
		system("cls");
		int midX = w / 2 - 25;
		int midY = h / 2 - 10;

		// 1. 상단 상태 정보 (현재 소지금 표시)
		goToXY(midX, midY);     cout << "==================================================";
		goToXY(midX, midY + 1); cout << "             [ POKEMON CENTER & SHOP ]            ";
		goToXY(midX, midY + 2); cout << "    YOUR GOLD : " << g_player.getmoney() << " G";
		goToXY(midX, midY + 3); cout << "==================================================";

		// 2. [핵심] 네가 Item.cpp에 작성한 "=== Item List ==="를 그대로 출력합니다.
		//goToXY를 하지 않고 바로 호출하면 네가 만든 cout들이 순서대로 출력됩니다.
		cout << "\n";
		Item::ShowAllItems();

		cout << "\n  Select Item Number: ";

		int choice;
		if (!(cin >> choice)) {
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}

		// 3. 네가 만든 Buy 함수들과 1:1로 연결 (Item.cpp 로직 실행)
		switch (choice) {
		case 1:
			Item::RareCandy(g_player);
			break;
		case 2:
			Item::BuyHPPotion(g_player);
			break;
		case 3:
			Item::BuyFHPPotion(g_player);
			break;
		case 4:
			Item::BuyMultiLens(g_player);
			break;
		case 5:
			Item::BuyPowerPotion(g_player);
			break;
		case 6:
			Item::Buyrandomexp(g_player);
			break;
		case 7:
			Item::Buyrandomgold(g_player);
			break;
		case 0:
			cout << "\n    >> Leaving the shop...";
			inShop = false;
			break;
		default:
			cout << "\n    >> Invalid choice!";
			break;
		}

		// 결과를 확인할 시간을 주기 위해 잠시 대기
		Sleep(1200);
	}
}
