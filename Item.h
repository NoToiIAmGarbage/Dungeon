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
    int hp, atk, def, state;
public:
    Item();
    // Item(string, int, int, int);

    /* Set & Get function*/
    int getHp();
    int getAtk();
    int getDef();
    void setHp(int);
    void setAtk(int);
    void setDef(int);
};

#endif // ITEM_H_INCLUDED
