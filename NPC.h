#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Player.h"
#include "Item.h"

using namespace std;

class Player;
class Item;

class NPC {
private:
    vector<Item> shop;

public:
    NPC(int lvl);
    
    void showOptions(Player&);

    void showShop(Player&);
};


#endif // NPC_H_INCLUDED
