#ifndef BACKPACK_H
#define BACKPACK_H

#include <vector>
#include <iomanip>
#include "Item.h"
#include "Player.h"
using namespace std;

class Player;
class Backpack;

class Backpack {
private:
	vector< pair<Item*, bool> > backpack;
	Item *helmet, *chest, *pants, *boots, *weapon;
public:
	void showBackpack(Player&);
	Backpack();

};


#endif