#include "GameCharacter.h"

// implement the basic functions

void GameCharacter::setMaxHealth(int value) {
	maxHealth = value;
}

void GameCharacter::setCurrentHealth(int value) {
	currentHealth = value;
}
void GameCharacter::setAttack(int value) {
	attack = value;
}
void GameCharacter::setDefense(int value) {
	defense = value;
}
void GameCharacter::setExp(int value) {
	exp = value;
}
int GameCharacter::getMaxHealth() {
	return maxHealth;
}
int GameCharacter::getCurrentHealth() {
	return currentHealth;
}
int GameCharacter::getAttack() {
	return attack;
}
int GameCharacter::getDefense() {
	return defense;
}
int GameCharacter::getExp() {
	return exp;
}

// implement the additional functions

bool GameCharacter::checkIsDead() {
	return currentHealth > 0;
}

void GameCharacter::takeDamage(int value) {
	currentHealth -= value;
	// TBD
}

// implement the constructor

GameCharacter::GameCharacter(string name) : name(name) {
	// TBD
}
GameCharacter::GameCharacter() : name("Test") {

}