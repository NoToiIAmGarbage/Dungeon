#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
using namespace std;

class Player;

class Item {
private:
    int attr, cost;
    string tag, name;
public:
    Item();
    Item(string, int, int);

    string getName();

    int getAttr();

    int getCost();

    string getShopTag();
};

#endif // ITEM_H_INCLUDED