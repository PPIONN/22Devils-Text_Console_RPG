#include "Common.h"
#include "GameData.h"

extern Player g_player;

void scene5() {
	int w, h;
	getActualSize(w, h);
	bool inShop = true;

	while (inShop) {
		system("cls");

		int midX = (w / 2) - 30;
		int midY = 3;

		// 상단 프레임 및 소지금 표시
		goToXY(midX, midY);     cout << "============================================================";
		goToXY(midX, midY + 1); cout << "               [ POKEMON CENTER & SHOP ]                    ";
		goToXY(midX, midY + 2); cout << "------------------------------------------------------------";
		goToXY(midX + 2, midY + 3); cout << "PLAYER : " << g_playerName;
		goToXY(midX + 35, midY + 3); cout << "YOUR GOLD : " << g_player.getmoney() << " G";
		goToXY(midX, midY + 4); cout << "============================================================";

		// 아이템 리스트 출력
		goToXY(midX + 5, midY + 6);  cout << "1. Rare Candy   - Level Up!           (500G)";
		goToXY(midX + 5, midY + 7);  cout << "2. HPPotion     - Restores 20 HP      (100G)";
		goToXY(midX + 5, midY + 8);  cout << "3. FHPPotion    - Full Restore HP     (100G)";
		goToXY(midX + 5, midY + 9);  cout << "4. MultiLens    - Double Attack       (200G)";
		goToXY(midX + 5, midY + 10); cout << "5. PowerPotion  - Attack +20          (100G)";
		goToXY(midX + 5, midY + 11); cout << "6. randomexp    - 50~500 EXP Box      (100G)";
		goToXY(midX + 5, midY + 12); cout << "7. randomgold   - 50~500 GOLD Box     (100G)";
		goToXY(midX + 5, midY + 13); cout << "0. Exit Shop";

		int inputY = midY + 16;
		goToXY(midX, inputY);     cout << "============================================================";
		goToXY(midX + 2, inputY + 1); cout << ">> Select Number : ";

		int choice;
		if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }

		goToXY(midX + 2, inputY + 3);
		switch (choice) {
		case 1: Item::RareCandy(g_player); break;
		case 2: Item::BuyHPPotion(g_player); break;
		case 3: Item::BuyFHPPotion(g_player); break;
		case 4: Item::BuyMultiLens(g_player); break;
		case 5: Item::BuyPowerPotion(g_player); break;

			// [수정] 6번과 7번은 구매(Buy) 후 즉시 사용(Use)하도록 연결
		case 6:
			Item::Buyrandomexp(g_player);
			Item::Userandomexp(g_player);
			break;
		case 7:
			Item::Buyrandomgold(g_player);
			Item::Userandomgold(g_player);
			break;

		case 0:
			cout << ">> Leaving shop...";
			Sleep(1000);
			inShop = false;
			break;
		default:
			cout << ">> Invalid choice!";
			Sleep(800);
			break;
		}

		if (choice != 0) Sleep(1200);
	}
}
