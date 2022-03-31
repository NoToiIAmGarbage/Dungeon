#include "Dungeon.h"
#include <windows.h>
#include <conio.h>

// Function supporting printing Room
void setCursorPosition(int y, int x) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

// self-explanary name
void Dungeon::showRoomChange() {
	system("cls");
	setCursorPosition(0, 0);
	for(int i = 0; i <= sizeX + 1; i ++) {
		for(int j = 0; j <= sizeY + 1; j ++) {
			if(i == 0 || i == sizeX + 1) {
				cout << '-';
			}
			else if(j == 0 || j == sizeY + 1) {
				cout << '|';
			} // the above are borders
			else if(i == player.getCurX() && j == player.getCurY()) {
				cout << facingTable[player.getFacing()];
			}
			else {
				cout << ' ';
			}
		}
		cout << '\n';
	}
}

// self-explanary name 
void Dungeon::showPlayerChange(int oriX, int oriY, int newX, int newY) {
	setCursorPosition(oriX, oriY);
	cout << ' ';
	setCursorPosition(newX, newY);
	cout << facingTable[player.getFacing()];
}

void Dungeon::createPlayer() {
	cout << "Please input your user name : ";
	string usrName; cin >> usrName;
	player = Player(usrName, sizeX, sizeY);
}

/* Create a map, which include several different rooms */
void Dungeon::createMap() {
	for(int i = 1; i <= roomX; i ++) {
		for(int j = 1; j <= roomY; j ++) {
			gameMap[i][j] = Room();
		}
	}
}

bool checkCoordValid(int x, int y) {
	
}

void Dungeon::handleAction(int actionType) {
	if(actionType <= 3) { // {up, down, left, right}
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
	}
	else {

	}
}

/* Deal with player's iteraction with objects in that room */
void handleEvent(Object*);

/* Deal with the player's action     */
/* including showing the action list */
/* that player can do at that room   */
/* and dealing with player's input   */
void chooseAction(vector<Object*>);

/* Check whether the game should end or not */
/* Including player victory, or he/she dead */
bool checkGameLogic();

/* Deal with the whole game process */
void Dungeon::runDungeon() {
	showRoomChange();
	char curInput;
	while(curInput = getch()) {
		if(curInput == 'w' || curInput == 'W') {
			handleAction(0);
		}
		else if(curInput == 's' || curInput == 'S') {
			handleAction(1);
		}
		else if(curInput == 'a' || curInput == 'A') {
			handleAction(2);
		}
		else if(curInput == 'd' || curInput == 'D') {
			handleAction(3);
		}
		else {
			break;
		}
	}
}


Dungeon::Dungeon() {
	sizeX = 11; sizeY = 25;
	createPlayer();
	createMap();
}