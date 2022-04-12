#include "Dungeon.h"
#include <windows.h>
#include <conio.h>
#include <time.h>

const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

// Function supporting printing Room
void setCursorPosition(int y, int x) {
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

// set output red
void setOutputRed() {
	SetConsoleTextAttribute(hOut, BACKGROUND_RED);
}

// set output white
void setOutputWhite() {
	SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
}

// set output green
void setOutputGreen() {
	SetConsoleTextAttribute(hOut, BACKGROUND_GREEN);
}

// set output original
void setOutputOriginal() {
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

// show status
void Dungeon::showStatus() {
	cout << "HP :  ";
	setOutputRed();
	for(int i = 0; i < player.getMaxHp(); i ++) {
		if(i == player.getHp()) {
			setOutputWhite();
		}
		cout << ' ';
	}
	cout << '\n';
	setOutputOriginal();
	cout << "EXP : ";
	setOutputGreen();
	for(int i = 0; i < player.getLvlUp(); i ++) {
		if(i == player.getExp()) {
			setOutputWhite();
		}
		cout << ' ';
	}
	cout << '\n';
	setOutputOriginal();
}

void Dungeon::showStatusPad() {
	system("cls");
	showStatus();
	player.showStatus();
	cout << "Press b to return\n";
	char c;
	while(c = getch()) {
		if(c == 'b' || c == 'B') {
			break;
		}
	}
	showRoomChange();
}

void Dungeon::showInventory() {
	system("cls");
	cout << "Press b to return\n";
	char c;
	while(c = getch()) {
		if(c == 'b' || c == 'B') {
			break;
		}
	}
	showRoomChange();
}

// self-explanary name
void Dungeon::showRoomChange() {
	system("cls");
	setCursorPosition(0, 0);
	for(int i = 0; i <= sizeX + 1; i ++) {
		for(int j = 0; j <= sizeY + 1; j ++) {
			cout << curMap[i][j];
		}
		cout << '\n';
	}
	showStatus();
	cout << "[E] : Status, [I] : Iventory\n";
}

// self-explanary name 
void Dungeon::showPlayerChange(int oriX, int oriY, int newX, int newY) {
	setCursorPosition(oriX, oriY);
	curMap[oriX][oriY] = ' ';
	cout << ' ';
	setCursorPosition(newX, newY);
	curMap[newX][newY] = facingTable[player.getFacing()];
	cout << facingTable[player.getFacing()];
}

void Dungeon::createPlayer() {
	cout << "Please input your user name : ";
	string usrName; cin >> usrName;
	player = Player(usrName);
}

/* Create a map, which include several different rooms */
void Dungeon::createMap() {
	srand(time(0));
	for(int i = 1; i <= roomX; i ++) {
		for(int j = 1; j <= roomY; j ++) {
			int d = rand() % 4;
			if(d == 0) {
				monsterRoomVec.push_back(new monsterRoom());
				gm[i][j] = monsterRoomVec.back();
				gameMap[i][j] = {d, monsterRoomVec.size() - 1};
			}
			else if(d == 1) {
				npcRoomVec.push_back(new npcRoom());
				gm[i][j] = npcRoomVec.back();
				gameMap[i][j] = {d, npcRoomVec.size() - 1};
			}
			else if(d == 2) {
				smithRoomVec.push_back(new smithRoom());
				gm[i][j] = smithRoomVec.back();
				gameMap[i][j] = {d, smithRoomVec.size() - 1};
			}
			else {
				chestRoomVec.push_back(new chestRoom());
				gm[i][j] = chestRoomVec.back();
				gameMap[i][j] = {d, chestRoomVec.size() - 1};
			}
		}
	}
}

bool Dungeon::checkCoordValid(int x, int y) {
	if(x > sizeX || x < 1 || y > sizeY || y < 1) {
		return false;
	}
	return true;
}

void Dungeon::handleMovement(int actionType) {
	player.setFacing(actionType);
	int dx = player.getCurX() + direx[actionType];
	int dy = player.getCurY() + direy[actionType];
	if(checkCoordValid(dx, dy)) {
		showPlayerChange(
			player.getCurX(), 
			player.getCurY(), 
			dx, dy
		);
		player.setCoord(dx, dy);
	}
	else {
		showPlayerChange(
			player.getCurX(), 
			player.getCurY(), 
			player.getCurX(),
			player.getCurY()
		);
	}
}

/* Check whether the game should end or not */
/* Including player victory, or he/she dead */
bool checkGameLogic();

/* Deal with the whole game process */
void Dungeon::runDungeon() {
	showRoomChange();
	char curInput;
	while(curInput = getch()) {
		if(curInput == 'w' || curInput == 'W') {
			handleMovement(0);
		}
		else if(curInput == 's' || curInput == 'S') {
			handleMovement(1);
		}
		else if(curInput == 'a' || curInput == 'A') {
			handleMovement(2);
		}
		else if(curInput == 'd' || curInput == 'D') {
			handleMovement(3);
		}
		else if(curInput == 'i' || curInput == 'I') {
			showInventory();
		}
		else if(curInput == 'e' || curInput == 'E') {
			showStatusPad();
		}
		else if(curInput == ' ') {
			int dx = player.getCurX() + direx[player.getFacing()];
			int dy = player.getCurY() + direy[player.getFacing()];
			if(checkCoordValid(dx, dy)) {
				if(obj[dx][dy] == 1) {

				} // monster
				else if(obj[dx][dy] == 2) {

				} // npc
				else if(obj[dx][dy] == 3) {

				} // smith
				else if(obj[dx][dy] == 4) {

				} // chest
				else if(obj[dx][dy] == 6) {

				} // exit
			}
		}
		else if(curInput == 'x') {
			break;
		}
	}
}


Dungeon::Dungeon() {
	createPlayer();
	createMap();
	gm[player.getCurX()][player.getCurY()] -> enterRoom(player, curMap, obj);
}