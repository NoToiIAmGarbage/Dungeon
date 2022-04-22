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
	if(gm[player.getMapX()][player.getMapY()] -> getRoomType() == "Exit Room" && !player.haveKey()) {
		timeout = true;
		system("cls");
		cout << "You haven't find the key to this room !!\n";
		Sleep(2000);
		timeout = false;
		thread {timer, this}.detach();
		player.setFacing(player.getFacing() / 2 * 2 + !(player.getFacing() % 2));
		changeRoom();
	}
	for(int i = 1; i <= 11; i ++) {
		for(int j = 1; j <= 25; j ++) {
			drop[i][j].clear();
		}
	}
	vis[player.getMapX()][player.getMapY()] = (gm[player.getMapX()][player.getMapY()] -> getRoomType())[0];
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
	cout << "[P] : pause, [X] : Exit\n";
	cout << "Current Room Position : " << player.getMapX() << ' ' << player.getMapY() << '\n';
	cout << "Current Room Type : " << (gm[player.getMapX()][player.getMapY()] -> getRoomType()) << '\n';
	for(int i = 0; i <= 12; i ++) {
		setCursorPosition(i, 48);
		for(int j = 0; j <= 32; j ++) {
			if(i == 0 || i == 12) {
				cout << '-';
			}
			else if(j == 0 || j == 32) {
				cout << '|';
			}
			else if((j - 1) % 3 == 0) {
				int x = i, y = (j - 1) / 3 + 1;
				if(player.getMapX() == x && player.getMapY() == y) {
					setOutputGreen();
					cout << vis[x][y];
					setOutputOriginal();
				}
				else {
					cout << vis[x][y];
				}
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
			if(d < tot / 10 * 6) {
				monsterRoomVec.push_back(new monsterRoom());
				gm[i][j] = monsterRoomVec.back();
			}
			else if(d >= tot / 10 * 6 && d < tot / 10 * 8) {
				npcRoomVec.push_back(new npcRoom());
				gm[i][j] = npcRoomVec.back();
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
	if(!remainTime) {
		gameEnd = true;
	}
}

void Dungeon::gameLose() {
	gameEnd = true;
	system("cls");
	cout << "You Died QQ\n";
	return;
}

void Dungeon::gameWon() {
	gameEnd = true;
	system("cls");
	cout << "You Win !!\n";
	return;
}

void Dungeon::outputTip() {
	cout << "\"  The Exit is at your ";
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
	cout << "\"";
}

/* Deal with the whole game process */
void Dungeon::runDungeon() {
	thread {timer, this}.detach();
	showRoomChange();
	char curInput;
	while(curInput = getch()) {
		if(gameEnd) {
			gameLose();
			break;
		}
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
						int k = randGen(0, 3);
						if(k) {
							obj[dx][dy] = 3;
							curMap[dx][dy] = '*';
							int t = remainTime % 6;
							Item tmp;
							if(t == 0) {
								int d = randGen(0, 10000) * remainTime % 3;
								int cost = d * 100 + randGen(0, 10000) * remainTime % 100;
								tmp = Item("helmet", d + 1, cost);
							}
							else if(t == 1) {
								int d = randGen(0, 10000) * remainTime % 3;
								int cost = d * 100 + randGen(0, 10000) * remainTime % 100;
								tmp = Item("chest", d + 1, cost);
							}
							else if(t == 2) {
								int d = randGen(0, 10000) * remainTime % 3;
								int cost = d * 100 + randGen(0, 10000) * remainTime % 100;
								tmp = Item("pants", d + 1, cost);
							}
							else if(t == 3) {
								int d = randGen(0, 10000) * remainTime % 3;
								int cost = d * 100 + randGen(0, 10000) * remainTime % 100;
								tmp = Item("boots", d + 1, cost);
							}
							else if(t == 4) {
								int d = player.getLvl() + randGen(0, 10000) * remainTime % 20;
								int cost = d * 100 + randGen(0, 10000) * remainTime % 100;
								tmp = Item("weapon", d, cost);
							}
							else {
								tmp = Item("potion", (4 + player.getLvl()) / 2, 60);
							}
							drop[dx][dy].push_back(tmp);
						}
						system("cls");
						setCursorPosition(0, 0);
						cout << "============================================\n";
						cout << "|   ";
						setOutputRed();
						outputTip();
						setOutputOriginal();
						cout << "   |\n";
						cout << "| A voice in your head suddenly appeared : |\n";
						cout << "|                                          |\n";
						cout << "============================================\n";
						setOutputOriginal();
						Sleep(2000);
						cout << "Press any key to procceed\n";
						char c = getch();
					}
					timeout = false;
					thread {timer, this}.detach();
					if(player.getHp() == 0) {
						gameLose();
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
					timeout = true;
					system("cls");
					for(Item x : drop[dx][dy]) {
						cout << '|';
						cout << setw(20) << x.getName();
						cout << "|" << x.getShopTag();
						cout << setw(2) << x.getAttr() << '|';
						cout << "COST : ";
						cout << setw(4) << x.getCost() << "|";
						cout << '\n';
					}
					cout << "[W] to scroll up, [S] to scroll down, [spacebar] to pick up, [B] to leave.\n";
					char c;
					int curPtr = 0;
					setCursorPosition(curPtr, 43);
					cout << '*';
					while(c = getch()) {
						if(c == 'w' || c == 'W') {
							if(curPtr > 0) {
								setCursorPosition(curPtr, 43);
								cout << ' ';
								curPtr --;
								setCursorPosition(curPtr, 43);
								cout << 'S';
							}
						}
						else if(c == 's' || c == 'S') {
							if(!drop[dx][dy].empty() && curPtr < drop[dx][dy].size() - 1) {
								setCursorPosition(curPtr, 43);
								cout << ' ';
								curPtr ++;
								setCursorPosition(curPtr, 43);
								cout << drop[dx][dy].size() - 1;
							}
						}
						else if(c == ' ') {
							if(curPtr < drop[dx][dy].size()) {
								system("cls");
								cout << "You picked up " << drop[dx][dy][curPtr].getName() << '\n';
								player.purchase(drop[dx][dy][curPtr]);
								player.gainMoney(drop[dx][dy][curPtr].getCost());
								Sleep(2000);
								drop[dx][dy].erase(drop[dx][dy].begin() + curPtr);
								system("cls");
								for(Item x : drop[dx][dy]) {
									cout << '|';
									cout << setw(20) << x.getName();
									cout << "|" << x.getShopTag();
									cout << setw(2) << x.getAttr() << '|';
									cout << "COST : ";
									cout << setw(4) << x.getCost() << "|";
								}
								curPtr = 0;
								cout << "[W] to scroll up, [S] to scroll down, [spacebar] to pick up, [B] to leave.\n";
							}
						}
						else if(c == 'b' || c == 'B') {
							break;
						}
					}
					if(drop[dx][dy].empty()) {
						obj[dx][dy] = 0;
						curMap[dx][dy] = ' ';
					}
					timeout = false;
					thread {timer, this}.detach();
					system("cls");
					showRoomChange();
				} // drops
				else if(obj[dx][dy] == 4) {
					timeout = true;
					system("cls");
					int t = remainTime %  5;
					Item tmp;
					if(t == 0) {
						int d = randGen(0, 10000) * remainTime % 3;
						int cost = d * 100 + randGen(0, 10000) * remainTime % 100;
						tmp = Item("helmet", d + 1, cost);
						player.purchase(tmp);
						player.gainMoney(cost);
					}
					else if(t == 1) {
						int d = randGen(0, 10000) * remainTime % 3;
						int cost = d * 100 + randGen(0, 10000) * remainTime % 100;
						tmp = Item("chest", d + 1, cost);
						player.purchase(tmp);
						player.gainMoney(cost);
					}
					else if(t == 2) {
						int d = randGen(0, 10000) * remainTime % 3;
						int cost = d * 100 + randGen(0, 10000) * remainTime % 100;
						tmp = Item("pants", d + 1, cost);
						player.purchase(tmp);
						player.gainMoney(cost);
					}
					else if(t == 3) {
						int d = randGen(0, 10000) * remainTime % 3;
						int cost = d * 100 + randGen(0, 10000) * remainTime % 100;
						tmp = Item("boots", d + 1, cost);
						player.purchase(tmp);
						player.gainMoney(cost);
					}
					else {
						int d = player.getLvl() + randGen(0, 10000) * remainTime % 20;
						int cost = d * 100 + randGen(0, 10000) * remainTime % 100;
						tmp = Item("weapon", d, cost);
						player.purchase(tmp);
						player.gainMoney(cost);
					}
					cout << "You've got " << tmp.getName() << '\n';
					Sleep(2000);
					curMap[dx][dy] = ' ';
					gm[player.getMapX()][player.getMapY()] = emptyRoomInstance;
					obj[dx][dy] = 0;
					system("cls");
					showRoomChange();
					timeout = false;
					thread {timer, this}.detach();
				} // chest
				else if(obj[dx][dy] == 5) {
					gameWon();
					break;
				} // exit
			}
			else if(checkIsDoor(dx, dy)) {
				changeRoom();
			}
		}
		else if(curInput == 'x') {
			system("cls");
			gameEnd = true;
			break;
		}
		else if(curInput == 'p') {
			timeout = true;
			system("cls");
			cout << "Paused, [b] to continue\n";
			char c;
			while(c = getch()) {
				if(c == 'b') {
					break;
				}
			}
			system("cls");
			showRoomChange();
			timeout = false;
			thread {timer, this}.detach();
		}
	}
}


Dungeon::Dungeon() {
	for(int i = 1; i <= roomSize; i ++) {
		for(int j = 1; j <= roomSize; j ++) {
			vis[i][j] = ' ';
		}
	}
	vis[6][6] = 'S';
	remainTime = 180; gameEnd = false;
	emptyRoomInstance = new emptyRoom;
	system("cls");
	createPlayer();
	createMap();
	gm[player.getMapX()][player.getMapY()] -> enterRoom(player, curMap, obj);
}