#include "NPC.h"

const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

// Function supporting printing Room
static void setCursorPosition(int y, int x) {
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

// set output red

NPC::NPC(int lvl) {
	srand(time(0));
	for(int i = 1; i <= 9; i ++) {
		int t = rand() % 5;
		if(t == 0) {
			int d = rand() % 3;
			int cost = d * 100 + rand() % 100;
			shop.push_back(Item("helmet", d, cost));
		}
		else if(t == 1) {
			int d = rand() % 3;
			int cost = d * 100 + rand() % 100;
			shop.push_back(Item("chest", d, cost));	
		}
		else if(t == 2) {
			int d = rand() % 3;
			int cost = d * 100 + rand() % 100;
			shop.push_back(Item("pants", d, cost));
		}
		else if(t == 3) {
			int d = rand() % 3;
			int cost = d * 100 + rand() % 100;
			shop.push_back(Item("boots", d, cost));
		}
		else {
			int d = lvl + rand() % 20;
			int cost = d * 100 + rand() % 100;
			shop.push_back(Item("weapon", d, cost));
		}
	}
	shop.push_back(Item("potion", (4 + lvl) / 2, 60));
}


void NPC::showShop(Player& player) {
	system("cls");
	setCursorPosition(0, 0);
	for(Item x : shop) {
		cout << '|';
		cout << setw(10) << x.getName();
		cout << "|" << x.getShopTag();
		cout << setw(2) << x.getAttr() << '|';
		cout << "COST : ";
		cout << setw(4) << x.getCost() << "| |\n";
	}
	cout << "[W] and [S] to scoll up and down, [spacebar] to purchase, [B] to leave\n";
	int curPtr = 0;
	setCursorPosition(0, 33);
	cout << '*';
	char c;
	while(c = getch()) {
		if(c == 'w' || c == 'W') {
			if(curPtr > 0) {
				curPtr --;
				setCursorPosition(curPtr + 1, 33);
				cout << ' ';
				setCursorPosition(curPtr, 33);
				cout << '*';
			}
		}
		else if(c == 's' || c == 'S') {
			if(curPtr < shop.size() - 1) {
				curPtr ++;
				setCursorPosition(curPtr - 1, 33);
				cout << ' ';
				setCursorPosition(curPtr, 33);
				cout << '*';
			}
		}
		else if(c == ' ') {

		}
		else if(c == 'b') {
			break;
		}
	}
}

void NPC::showOptions(Player& player) {
	system("cls");
	
	cout << '\n';

	cout << " * Shop\n\n";
	cout << "   Recover Hp\n\n";

	cout << "[W] and [S] to scoll up and down, [spacebar] to choose, [B] to leave shop\n";

	int curPtr = 1;

	char c;
	while(c = getch()) {
		if(c == 'w' || c == 'W') {
			if(curPtr > 1) {
				curPtr -= 2;
				setCursorPosition(3, 1);
				cout << ' ';
				setCursorPosition(1, 1);
				cout << '*';
			}
		}
		else if(c == 's' || c == 'S') {
			if(curPtr < 3) {
				curPtr += 2;
				setCursorPosition(1, 1);
				cout << ' ';
				setCursorPosition(3, 1);
				cout << '*';
			}
		}
		else if(c == 'b' || c == 'B') {
			break;
		}
		else if(c == ' ') {
			if(curPtr == 1) {
				showShop(player);
				system("cls");
				setCursorPosition(0, 0);
				cout << '\n';
				cout << " * Shop\n\n";
				cout << "   Recover Hp\n\n";
				cout << "[W] and [S] to scoll up and down, [spacebar] to choose, [b] to leave npc\n";
			}
			else if(curPtr == 3) {
				player.recover();
				system("cls");
				setCursorPosition(0, 0);
				cout << "You've recovered from the fatigue, hp is now full.\n";
				Sleep(2000);
				system("cls");
				setCursorPosition(0, 0);
				cout << '\n';

				cout << " * Shop\n\n";
				cout << "   Recover Hp\n\n";

				cout << "[W] and [S] to scoll up and down, [spacebar] to choose, [b] to leave npc\n";

				curPtr = 1;
			}
		}
	}
}