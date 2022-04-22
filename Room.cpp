#include "Room.h"

void Room::initializeMap(Player& player, char(*curMap)[sizeY + 2], int(*obj)[sizeY + 2]) {
	for(int i = 0; i <= sizeX + 1; i ++) {
		for(int j = 0; j <= sizeY + 1; j ++) {
			obj[i][j] = 0;
		}
	}
	int midX = (sizeX / 2) + 1, midY = (sizeY / 2) + 1;
	if(player.getFacing() == 0) {
		player.setCurX(sizeX);
		player.setCurY(midY);
	}
	else if(player.getFacing() == 1) {
		player.setCurX(1);
		player.setCurY(midY);
	}
	else if(player.getFacing() == 2) {
		player.setCurX(midX);
		player.setCurY(sizeY);
	}
	else {
		player.setCurX(midX);
		player.setCurY(1);
	}
	obj[player.getCurX()][player.getCurY()] = 10;
	obj[midX][1] = obj[midX][sizeY] = obj[1][midY] = obj[sizeX][midY] = 10;
	for(int i = 0; i <= sizeX + 1; i ++) {
		for(int j = 0; j <= sizeY + 1; j ++) {
			if(i == 0 || i == sizeX + 1) {
				if(j == sizeY / 2 + 1) {
					curMap[i][j] = ' ';
				}
				else {
					curMap[i][j] = '-';
				}
			}
			else if(j == 0 || j == sizeY + 1) {
				if(i == sizeX / 2 + 1) {
					curMap[i][j] = ' ';
				}
				else {
					curMap[i][j] = '|';
				}
			} // the above are borders
			else if(i == player.getCurX() && j == player.getCurY()) {
				curMap[i][j] = facingTable[player.getFacing()];
			}
			else {
				curMap[i][j] = ' ';
			}
		}
	}
}


void monsterRoom::addMonster(int x, int y) {
	monster.push_back({{x, y}, Monster()});
}


void npcRoom::enterRoom(Player& player, char(*curMap)[sizeY + 2], int(*obj)[sizeY + 2]) {
	initializeMap(player, curMap, obj);
	int midX = (sizeX / 2) + 1, midY = (sizeY / 2) + 1;
	obj[midX][midY] = 2;
	curMap[midX][midY] = 'N';
}

void monsterRoom::enterRoom(Player& player, char(*curMap)[sizeY + 2], int(*obj)[sizeY + 2]) {
	initializeMap(player, curMap, obj);	
	srand(time(0));
	int t = rand() % 10 + 1;
	for(int i = 0; i < t; i ++) {
		int x = rand() % sizeX + 1, y = rand() % sizeY + 1;
		while(obj[x][y]) {
			x = rand() % sizeX + 1, y = rand() % sizeY + 1;
		}
		curMap[x][y] = 'M';
		obj[x][y] = 1;
		addMonster(x, y);
	}
}

void chestRoom::enterRoom(Player& player, char(*curMap)[sizeY + 2], int(*obj)[sizeY + 2]) {
	initializeMap(player, curMap, obj);
	srand(time(0));
	int t = rand() % 2;
	int midX = (sizeX / 2) + 1, midY = (sizeY / 2) + 1;
	curMap[midX][midY] = 'C';
	if(t) { // it is a chest
		obj[midX][midY] = 4;
	}
	else { // trap chest, a monster
		obj[midX][midY] = 1;
	}
}

void smithRoom::enterRoom(Player& player, char(*curMap)[sizeY + 2], int(*obj)[sizeY + 2]) {
	initializeMap(player, curMap, obj);
	int midX = (sizeX / 2) + 1, midY = (sizeY / 2) + 1;
	curMap[midX][midY] = 'S';
	obj[midX][midY] = 3;
}

void exitRoom::enterRoom(Player& player, char(*curMap)[sizeY + 2], int(*obj)[sizeY + 2]) {
	initializeMap(player, curMap, obj);
	int midX = (sizeX / 2) + 1, midY = (sizeY / 2) + 1;
	curMap[midX][midY] = 'E';
	obj[midX][midY] = 5;
}

void startRoom::enterRoom(Player& player, char(*curMap)[sizeY + 2], int(*obj)[sizeY + 2]) {
	initializeMap(player, curMap, obj);
}

void emptyRoom::enterRoom(Player& player, char(*curMap)[sizeY + 2], int(*obj)[sizeY + 2]) {
	initializeMap(player, curMap, obj);	
}
string chestRoom::getRoomType() {
	return "Chest Room";
}

string npcRoom::getRoomType() {
	return "Npc Room";
}

string monsterRoom::getRoomType() {
	return "Monster Room";
}

string exitRoom::getRoomType() {
	return "Exit Room";
}

string startRoom::getRoomType() {
	return "Start Room";
}

string smithRoom::getRoomType() {
	return "Smith Room";
}

string emptyRoom::getRoomType() {
	return "Empty Room";
}