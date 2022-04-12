#include "Player.h"

Player::Player() {
}

Player::Player(string name) {
	setCoord(sizeX / 2 + 1, sizeY / 2 + 1);
	setFacing(0);
	setHp(5); setMaxHp(10); setAtk(5);
	setExp(5); setLvl(1); setLvlUp(10);
}

void Player::setCoord(int x, int y) {
	curX = x; curY = y;
}
int Player::getCurX() {
	return curX;
}
int Player::getCurY() {
	return curY;
}

int Player::getFacing() {
	return facing;
}
void Player::setFacing(int value) {
	facing = value;
}

// showStatus
void Player::showStatus() {
	cout << "ATK : " << getAtk() << '\n';
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