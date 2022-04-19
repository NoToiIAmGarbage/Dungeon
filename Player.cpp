#include "Player.h"

Player::Player() {

}

Player::Player(string name) {
	setCurX(sizeX / 2 + 1);
	setCurY(sizeY / 2 + 1);
	setMapX(roomSize / 2 + 1);
	setMapY(roomSize / 2 + 1);
	setFacing(0);
	setHp(3); setMaxHp(3); setAtk(5);
	setExp(0); setLvl(1); setLvlUp(5);
	money = 1000;

	items.reserve(100);
	bp = new Backpack;
}

void Player::setCurX(int value) {
	curX = value;
}
void Player::setCurY(int value) {
	curY = value;
}
int Player::getCurX() {
	return curX;
}
int Player::getCurY() {
	return curY;
}

int Player::getMapX() {
	return mapX;
}
int Player::getMapY() {
	return mapY;
}

void Player::setMapX(int value) {
	mapX = value;
}
void Player::setMapY(int value) {
	mapY = value;
}

int Player::getFacing() {
	return facing;
}
void Player::setFacing(int value) {
	facing = value;
}

void Player::setMaxHp(int value) {
	maxHp = value;
}

void Player::setHp(int value) {
	hp = value;
}
void Player::setAtk(int value) {
	atk = value;
}
void Player::setExp(int value) {
	exp = value;
}
void Player::setLvl(int value) {
	lvl = value;
}
void Player::setLvlUp(int value) {
	lvlUp = value;
}
int Player::getMaxHp() {
	return maxHp;
}
int Player::getHp() {
	return hp;
}
int Player::getAtk() {
	return atk;
}
int Player::getExp() {
	return exp;
}
int Player::getLvl() {
	return lvl;
}
int Player::getLvlUp() {
	return lvlUp;
}

const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

// set output red
static void setOutputRed() {
	SetConsoleTextAttribute(hOut, BACKGROUND_RED);
}

// set output white
static void setOutputWhite() {
	SetConsoleTextAttribute(hOut, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
}

// set output green
static void setOutputGreen() {
	SetConsoleTextAttribute(hOut, BACKGROUND_GREEN);
}

// set output original
static void setOutputOriginal() {
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void Player::showStatus() {
	cout << "HP :  ";
	setOutputRed();
	for(int i = 0; i < maxHp; i ++) {
		if(i == hp) {
			setOutputWhite();
		}
		cout << ' ';
	}
	cout << '\n';
	setOutputOriginal();
	cout << "EXP : ";
	setOutputGreen();
	for(int i = 0; i < lvlUp; i ++) {
		if(i == exp) {
			setOutputWhite();
		}
		cout << ' ';
	}
	setOutputOriginal();
	cout << " ( lvl : " << lvl << " )\n";
	cout << "$" << money << '\n';
}

void Player::gainExp(int value) {
	exp += value;
	if(exp >= lvlUp) {
		lvl ++;
		hp ++;
		exp -= lvlUp;
		lvlUp += 2;
	}
}

void Player::recover() {
	hp = maxHp;
}


void Player::showBackpack() {
	bp -> showBackpack(*this);
}

void Player::gainMoney(int value) {
	money += value;
}

int Player::getMoney() {
	return money;
}

void Player::purchase(Item item) {
	money -= item.getCost();
	items.push_back(item);
	cout << &items.back() << '\n';
	bp -> pickup(items.back());
}

void Player::addAtk(int attr) {
	atk += attr;
}

void Player::addHp(int attr) {
	maxHp += attr;
}

void Player::downAtk(int attr) {
	atk -= attr;
}

void Player::downHp(int attr) {
	maxHp -= attr;
	hp = min(maxHp, hp);
}

void Player::getKey() {
	bp -> setKey(true);
}

void Player::gainHp(int value) {
	hp += value;
	hp = min(maxHp, hp);
}