#include "NPC.h"

const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

// Function supporting printing Room
static void setCursorPosition(int y, int x) {
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

static int randGen(int left, int right) {

	using clk = chrono::high_resolution_clock;
	using rand_int = uniform_int_distribution<int>;
	using rand_double = uniform_real_distribution<double>;

	mt19937 rng(clk::now().time_since_epoch().count());
    return rand_int(left, right)(rng);
}


NPC::NPC(int lvl) {
	for(int i = 1; i <= 9; i ++) {
		int t = randGen(1, 4) * randGen(5, 9) * i % 5;
		if(t == 0) {
			int d = randGen(0, 10000) * i % 3;
			int cost = d * 100 + randGen(0, 10000) * i % 100;
			shop.push_back(Item("helmet", d + 1, cost));
		}
		else if(t == 1) {
			int d = randGen(0, 10000) * i % 3;
			int cost = d * 100 + randGen(0, 10000) * i % 100;
			shop.push_back(Item("chest", d + 1, cost));	
		}
		else if(t == 2) {
			int d = randGen(0, 10000) * i % 3;
			int cost = d * 100 + randGen(0, 10000) * i % 100;
			shop.push_back(Item("pants", d + 1, cost));
		}
		else if(t == 3) {
			int d = randGen(0, 10000) * i % 3;
			int cost = d * 100 + randGen(0, 10000) * i % 100;
			shop.push_back(Item("boots", d + 1, cost));
		}
		else {
			int d = lvl + randGen(0, 10000) * i % 20;
			int cost = d * 100 + randGen(0, 10000) * i % 100;
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
		cout << setw(20) << x.getName();
		cout << "|" << x.getShopTag();
		cout << setw(2) << x.getAttr() << '|';
		cout << "COST : ";
		cout << setw(4) << x.getCost() << "| |\n";
	}
	cout << "[W] and [S] to scoll up and down, [spacebar] to purchase, [B] to leave\n";
	int curPtr = 0;
	setCursorPosition(0, 43);
	cout << '*';
	char c;
	while(c = getch()) {
		if(c == 'w' || c == 'W') {
			if(curPtr > 0) {
				curPtr --;
				setCursorPosition(curPtr + 1, 43);
				cout << ' ';
				setCursorPosition(curPtr, 43);
				cout << '*';
			}
		}
		else if(c == 's' || c == 'S') {
			if(curPtr < shop.size() - 1) {
				curPtr ++;
				setCursorPosition(curPtr - 1, 43);
				cout << ' ';
				setCursorPosition(curPtr, 43);
				cout << '*';
			}
		}
		else if(c == ' ') {
			if(shop[curPtr].getCost() <= player.getMoney()) {
				player.purchase(shop[curPtr]);
				system("cls");
				setCursorPosition(0, 0);
				cout << "Purchased " << shop[curPtr].getName() << '\n';
				shop.erase(shop.begin() + curPtr);
				Sleep(2000);
			}
			else {
				system("cls");
				setCursorPosition(0, 0);
				cout << "Not enough money : (\n";
				Sleep(2000);
			}
			system("cls");
			setCursorPosition(0, 0);
			for(Item x : shop) {
				cout << '|';
				cout << setw(20) << x.getName();
				cout << "|" << x.getShopTag();
				cout << setw(2) << x.getAttr() << '|';
				cout << "COST : ";
				cout << setw(4) << x.getCost() << "| |\n";
			}
			cout << "[W] and [S] to scoll up and down, [spacebar] to purchase, [B] to leave\n";

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