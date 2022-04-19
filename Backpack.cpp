#include "Backpack.h"

const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

// Function supporting printing Room
static void setCursorPosition(int y, int x) {
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

Backpack::Backpack() {
	key = false;
	helmet = chest = pants = boots = weapon = nullptr;
}

void Backpack::output() {
	cout << "EQUIPED :\n";
	if(helmet != nullptr) {
		cout << "|  HEAD|" << setw(20) << helmet -> getName() << '|' << '\n';
	}
	else {
		cout << "|  HEAD|" << setw(20) << "EMPTY" << '|' << '\n';	
	}
	if(chest != nullptr) {
		cout << "| CHEST|" << setw(20) << chest -> getName() << '|' << '\n';
	}
	else {
		cout << "| CHEST|" << setw(20) << "EMPTY" << '|' << '\n';
	}
	if(pants != nullptr) {
		cout << "| PANTS|" << setw(20) << pants -> getName() << '|' << '\n';
	}
	else {
		cout << "| PANTS|" << setw(20) << "EMPTY" << '|' << '\n';	
	}
	if(boots != nullptr) {
		cout << "| BOOTS|" << setw(20) << boots -> getName() << '|' << '\n';	
	}
	else {
		cout << "| BOOTS|" << setw(20) << "EMPTY" << '|' << '\n';	
	}
	if(weapon != nullptr) {
		cout << "|WEAPON|" << setw(20) << weapon -> getName() << '|' << '\n';
	}
	else {
		cout << "| BOOTS|" << setw(20) << "EMPTY" << '|' << '\n';	 
	}
	cout << "=============================\n";
	cout << "Owned : \n";
	for(Item* x : backpack) {
		cout << '|';
		cout << setw(20) << x -> getName();
		cout << "|" << x -> getShopTag();
		cout << setw(2) << x -> getAttr() << '|';
		cout << "COST : ";
		cout << setw(4) << x -> getCost() << "|";
		if(x -> getState()) {
			cout << "ON|\n";
		}
		else {
			cout << "  |\n";
		}
	}
	if(key) {
		cout << "|" << setw(20) << "The Exit's key" << "|        |           |  |";
	}
	cout << "\n[W] and [S] to scoll up and down, [spacebar] to purchase, [B] to leave\n";
}

void Backpack::showBackpack(Player& player) {
	output();
	char c;
	int curPtr = 8;
	while(c = getch()) {
		if(c == 'w' || c == 'W') {
			if(curPtr > 8) {
				curPtr --;
				setCursorPosition(curPtr + 1, 46);
				cout << ' ';
				setCursorPosition(curPtr, 46);
				cout << '*';
			}
			else if(curPtr == 8 && !backpack.empty()) {
				curPtr -= 3;
				setCursorPosition(curPtr + 3, 46);
				cout << ' ';
				setCursorPosition(curPtr, 29);
				cout << '*';	
			}
			else if(curPtr > 1) {
				curPtr --;
				setCursorPosition(curPtr + 1, 29);
				cout << ' ';
				setCursorPosition(curPtr, 29);
				cout << '*';
			}
		}
		else if(c == 's' || c == 'S') {
			if(curPtr < 5) {
				curPtr ++;
				setCursorPosition(curPtr - 1, 29);
				cout << ' ';
				setCursorPosition(curPtr, 29);
				cout << '*';
			}
			else if(curPtr == 5) {
				curPtr += 3;
				setCursorPosition(curPtr - 3, 29);
				cout << ' ';
				setCursorPosition(curPtr, 46);
				cout << '*';	
			}
			else if(curPtr < backpack.size() - 1 + 8) {
				curPtr ++;
				setCursorPosition(curPtr - 1, 46);
				cout << ' ';
				setCursorPosition(curPtr, 46);
				cout << '*';
			}
		}
		else if(c == ' ') {
			if(curPtr >= 8) {
				if(!backpack[curPtr - 8] -> getState()) {
					if(backpack[curPtr - 8] -> getTag() == "helmet") {
						if(helmet != nullptr) {
							helmet -> unEquip(player);
						}
						helmet = backpack[curPtr - 8];
						helmet -> equip(player);

					}
					else if(backpack[curPtr - 8] -> getTag() == "chest") {
						if(chest != nullptr) {
							chest -> unEquip(player);
						}
						chest = backpack[curPtr - 8];
						chest -> equip(player);
					}
					else if(backpack[curPtr - 8] -> getTag() == "pants") {
						if(pants != nullptr) {
							pants -> unEquip(player);
						}
						pants = backpack[curPtr - 8];
						pants -> equip(player);
					}
					else if(backpack[curPtr - 8] -> getTag() == "boots") {
						if(boots != nullptr) {
							boots -> unEquip(player);
						}
						boots = backpack[curPtr - 8];
						boots -> equip(player);
					}
					else if(backpack[curPtr - 8] -> getTag() == "weapon") {
						if(weapon != nullptr) {
							weapon -> unEquip(player);
						}
						weapon = backpack[curPtr - 8];
						weapon -> equip(player);
					}
					else if(backpack[curPtr - 8] -> getTag() == "potion") {
						player.gainHp(backpack[curPtr - 8] -> getAttr());
						system("cls");
						cout << "You've drinked the potion and gain some health!\n";
						backpack.erase(backpack.begin() + curPtr - 8);
						Sleep(1000);
					}
					system("cls");
					output();
				}
			}
			else {
				if(curPtr == 1) {
					if(helmet != nullptr) {
						helmet -> unEquip(player);
						helmet = nullptr;
						system("cls");
						output();
						curPtr = 8;
						setCursorPosition(8, 46);
						cout << '*';
					}
				}
				else if(curPtr == 2) {
					if(chest != nullptr) {
						chest -> unEquip(player);
						chest = nullptr;
						system("cls");
						output();
						curPtr = 8;
						setCursorPosition(8, 46);
						cout << '*';
					}
				}
				else if(curPtr == 3) {
					if(pants != nullptr) {
						pants -> unEquip(player);
						pants = nullptr;
						system("cls");
						output();
						curPtr = 8;
						setCursorPosition(8, 46);
						cout << '*';
					}
				}
				else if(curPtr == 4) {
					if(boots != nullptr) {
						boots -> unEquip(player);
						boots = nullptr;
						system("cls");
						output();
						curPtr = 8;
						setCursorPosition(8, 46);
						cout << '*';
					}
				}
				else if(curPtr == 5) {
					if(weapon != nullptr) {
						weapon -> unEquip(player);
						weapon = nullptr;
						system("cls");
						output();
						curPtr = 8;
						setCursorPosition(8, 46);
						cout << '*';
					}
				}
			}

		}
		else if(c == 'b' || c == 'B') {
			break;
		}
	}
}

void Backpack::pickup(Item& item) {
	Item* ptr = &item;
	backpack.push_back(ptr);	
}

void Backpack::setKey(bool value) {
	key = value;
}