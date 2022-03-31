#include "Player.h"

Player::Player() {
}

Player::Player(string name, int sizeX, int sizeY) {
	setCoord(sizeX / 2, sizeY / 2);
	setFacing(0);
}

void Player::triggerEvent(Object*) {

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