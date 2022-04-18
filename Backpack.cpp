#include "Backpack.h"

const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

// Function supporting printing Room
static void setCursorPosition(int y, int x) {
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

Backpack::Backpack() {

}

void Backpack::showBackpack(Player& player) {
	cout << "|EQUIPED : \n";
	if(helmel != nullptr) {
		cout << "|  HEAD|" << setw(10) << helmet.getName() << '|' << '\n';
	}
	else {
		cout << "|  HEAD|" << setw(10) << "EMPTY" << '|' << '\n';	
	}
	if(chest != nullptr) {
		cout << "| CHEST|" << setw(10) << chest.getName() << '|' << '\n';
	}
	else {
		cout << "| CHEST|" << setw(10) << "EMPTY" << '|' << '\n';
	}
	if(pants != nullptr) {
		cout << "| PANTS|" << setw(10) << pants.getName() << '|' << '\n';
	}
	else {
		cout << "| PANTS|" << setw(10) << "EMPTY" << '|' << '\n';	
	}
	if(boots != nullptr) {
		cout << "| BOOTS|" << setw(10) << boots.getName() << '|' << '\n';	
	}
	else {
		cout << "| BOOTS|" << setw(10) << pants.getName() << '|' << '\n';	
	}
	
	cout << "|WEAPON|" << setw(10) << weapon.getName() << '|' << '\n';
	cout << "================================\n";
	for(auto x : backpack) {
		cout << '|';
		cout << setw(10) << x.first.getName();
		cout << "|" << x.first.getShopTag();
		cout << setw(2) << x.first.getAttr() << '|';
		cout << "COST : ";
		cout << setw(4) << x.first.getCost() << "|";
		if(x.second) {
			cout << "ON| |\n";
		}
		else {
			cout << "  | |\n";
		}
	}
	cout << "[W] and [S] to scoll up and down, [spacebar] to purchase, [B] to leave\n";
	char c;
	int curPtr = 7;
	while(c = getch()) {
		if(c == 'w' || c == 'W') {
			if(curPtr > 7) {
				curPtr --;
				setCursorPosition(curPtr + 1, 36);
				cout << ' ';
				setCursorPosition(curPtr, 36);
				cout << '*';
			}
		}
		else if(c == 's' || c == 'S') {
			if(curPtr < backpack.size() - 1 + 6) {
				curPtr ++;
				setCursorPosition(curPtr - 1, 36);
				cout << ' ';
				setCursorPosition(curPtr, 36);
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