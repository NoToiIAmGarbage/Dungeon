#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include "Player.h"
using namespace std;

class Player;

class Item {
private:
    int attr, cost, state;
    string tag, name;
public:
    Item();
    Item(string, int, int);

    string getName();

    string getTag();

    int getAttr();

    bool getState();

    int getCost();

    string getShopTag();

    void equip(Player&);

    void unEquip(Player&);
};

#endif // ITEM_H_INCLUDED