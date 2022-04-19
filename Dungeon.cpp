#include "Dungeon.h"


int Dungeon::getRemainTime() {
	return remainTime;
}

int randGen(int left, int right) {

	using clk = chrono::high_resolution_clock;
	using rand_int = uniform_int_distribution<int>;
	using rand_double = uniform_real_distribution<double>;

	mt19937 rng(clk::now().time_since_epoch().count());
    return rand_int(left, right)(rng);
}

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

void Dungeon::changeRoom() {
	int dx = player.getMapX() + direx[player.getFacing()];
	int dy = player.getMapY() + direy[player.getFacing()];
	if(dx > roomSize || dx < 1 || dy > roomSize || dy < 1) {
		return;
	}
	player.setMapX(dx); player.setMapY(dy);
	gm[player.getMapX()][player.getMapY()] -> enterRoom(player, curMap, obj);
	showRoomChange();
}


void Dungeon::showStatusPad() {
	system("cls");
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
	player.showBackpack();
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
	player.showStatus();
	cout << "[E] : Status, [I] : Iventory\n";
	cout << "Current Room Position : " << player.getMapX() << ' ' << player.getMapY() << '\n';
	cout << "Current Room Type : " << (gm[player.getMapX()][player.getMapY()] -> getRoomType()) << '\n';
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
	start = new startRoom;
	exit = new exitRoom;
	gm[roomSize / 2 + 1][roomSize / 2 + 1] = start;
	desX = randGen(0, 100) % roomSize + 1;
	desY = randGen(0, 100) % roomSize + 1;
	while(abs(desX - (roomSize / 2 + 1)) + abs(desY - (roomSize / 2 + 1)) < roomSize / 2) {
		desX = randGen(0, 100) % roomSize + 1;
		desY = randGen(0, 100) % roomSize + 1;
	}
	gm[desX][desY] = exit;
	assert(gm[roomSize / 2 + 1][roomSize / 2 + 1] == start);
	assert(gm[desX][desY] == exit);
	for(int i = 1; i <= roomSize; i ++) {
		for(int j = 1; j <= roomSize; j ++) {
			if(i == roomSize / 2 + 1 && j == roomSize / 2 + 1) {
				continue;
			}
			if(i == desX && j == desY) {
				continue;
			}
			int d = i * (roomSize - 1) + j;
			int tot = roomSize * roomSize;
			if(d < tot / 10 * 5) {
				monsterRoomVec.push_back(new monsterRoom());
				gm[i][j] = monsterRoomVec.back();
			}
			else if(d >= tot / 10 * 5 && d < tot / 10 * 7) {
				npcRoomVec.push_back(new npcRoom());
				gm[i][j] = npcRoomVec.back();
			}
			else if(d >= tot / 10 * 7 && d < tot / 10 * 9) {
				smithRoomVec.push_back(new smithRoom());
				gm[i][j] = smithRoomVec.back();
			}
			else {
				chestRoomVec.push_back(new chestRoom());
				gm[i][j] = chestRoomVec.back();
			}
		}
	}
	assert(gm[roomSize / 2 + 1][roomSize / 2 + 1] == start);
	assert(gm[desX][desY] == exit);
	for(int i = 0; i < 30000; i ++) {
		int x1 = randGen(0, 100) % roomSize + 1;
		int y1 = randGen(0, 100) % roomSize + 1;
		while((x1 == roomSize / 2 + 1 && y1 == roomSize / 2 + 1) || 
			  (x1 == desX && y1 == desY)) {
			x1 = randGen(0, 100) % roomSize + 1;
			y1 = randGen(0, 100) % roomSize + 1;
		}
		int x2 = randGen(0, 100) % roomSize + 1;
		int y2 = randGen(0, 100) % roomSize + 1;
		while((x2 == roomSize / 2 + 1 && y2 == roomSize / 2 + 1) || 
			  (x2 == desX && y2 == desY)) {
			x2 = randGen(0, 100) % roomSize + 1;
			y2 = randGen(0, 100) % roomSize + 1;
		}
		swap(gm[x1][y1], gm[x2][y2]);
	}
	assert(gm[roomSize / 2 + 1][roomSize / 2 + 1] == start);
	assert(gm[desX][desY] == exit);
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
	if(checkCoordValid(dx, dy) && (!obj[dx][dy] || obj[dx][dy] == 10)) {
		showPlayerChange(
			player.getCurX(), 
			player.getCurY(), 
			dx, dy
		);
		player.setCurX(dx);
		player.setCurY(dy);
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

bool Dungeon::checkIsDoor(int x, int y) {
	int midX = (sizeX / 2) + 1, midY = (sizeY / 2) + 1;
	if(x == 0 && y == midY)  {
		return true;
	}
	if(x == sizeX + 1 && y == midY) {
		return true;
	}
	if(x == midX && y == 0) {
		return true;
	}
	if(x == midX && y == sizeY + 1) {
		return true;
	}
	return false;
}
void Dungeon::timer() {
	while(remainTime) {
		if(timeout || gameEnd) {
			break;
		}
		setCursorPosition(6, 28);
		setOutputRed();
		cout << remainTime -- << " secs remaining!!\n";
		setOutputOriginal();
		Sleep(1000);
	}
}

void Dungeon::endGame() {
	system("cls");
	cout << "You fucking died\n";
	cout << "LOL you sucks\n";
	return;
}

void Dungeon::outputTip() {
	cout << "\"The Exit is at your ";
	if(player.getMapX() >= desX) {
		cout << "top ";
	}
	else {
		cout << "botton ";
	}
	if(player.getMapY() >= desY) {
		cout << "left";
	}
	else {
		cout << "right";
	}
	cout << "\"\n";
}

/* Deal with the whole game process */
void Dungeon::runDungeon() {
	thread {timer, this}.detach();
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
			timeout = true;
			showInventory();
			timeout = false;
			thread {timer, this}.detach();
		}
		else if(curInput == 'e' || curInput == 'E') {
			timeout = true;
			showStatusPad();
			timeout = false;
			thread {timer, this}.detach();
		}
		else if(curInput == ' ') {
			int dx = player.getCurX() + direx[player.getFacing()];
			int dy = player.getCurY() + direy[player.getFacing()];
			if(checkCoordValid(dx, dy)) {
				if(obj[dx][dy] == 1) {
					Monster encounter(player.getLvl());
					timeout = true;
					bool d = encounter.combat(player);
					if(d) {
						obj[dx][dy] = 0;
						curMap[dx][dy] = ' ';
						system("cls");
						setCursorPosition(0, 0);
						outputTip();
						cout << "A voice in your head suddenly appeared:\n";
						Sleep(2000);
						cout << "Press any key to procceed\n";
						char c = getch();
					}
					timeout = false;
					thread {timer, this}.detach();
					if(player.getHp() == 0) {
						endGame();
						return;
					}
					showRoomChange();
				} // monster
				else if(obj[dx][dy] == 2) {
					NPC encounter(player.getLvl());
					timeout = true;
					encounter.showOptions(player);
					timeout = false;
					thread {timer, this}.detach();
					showRoomChange();
				} // npc
				else if(obj[dx][dy] == 3) {

				} // smith
				else if(obj[dx][dy] == 4) {

				} // chest
				else if(obj[dx][dy] == 5) {

				} // exit
			}
			else if(checkIsDoor(dx, dy)) {
				changeRoom();
			}
		}
		else if(curInput == 'x') {
			gameEnd = true;
			break;
		}
	}
}


Dungeon::Dungeon() {
	remainTime = 180; gameEnd = false;
	createPlayer();
	createMap();
	gm[player.getMapX()][player.getMapY()] -> enterRoom(player, curMap, obj);
}