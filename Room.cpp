#include "Room.h"

void Room::initializeMap(Player& player, char(*curMap)[sizeY + 2], int(*obj)[sizeY + 2]) {
	memset(obj, 0, sizeof(obj));
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
	obj[player.curX][player.curY] = 10;
	obj[midX][1] = obj[midX][25] = obj[1][midY] = obj[10][midY] = 10;
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
	int xMid = (sizeX / 2) + 1, yMid = (sizeY / 2) + 1;
	obj[sizeX][sizeY] = 2; 
}

void monsterRoom::enterRoom(Player& player, char(*curMap)[sizeY + 2], int(*obj)[sizeY + 2]) {
	initializeMap(player, curMap, obj);	
	srand(time(0));
	int t = rand() % 10;
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
	
}