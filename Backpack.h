#ifndef BACKPACK_H
#define BACKPACK_H

#include <vector>
#include <iomanip>
#include "Item.h"
#include "Player.h"
using namespace std;

class Player;
class Item;

class Backpack {
private:
	vector<Item*> backpack;
	Item *helmet, *chest, *pants, *boots, *weapon;
	int key;
public:
	void showBackpack(Player&);
	Backpack();

	void pickup(Item&);

	void output();

	void setKey(bool);

	bool haveKey();
};


#endif