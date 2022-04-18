#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Room.h"
#include "Backpack.h"
#include "Item.h"

using namespace std;

class Item;

class Player {
private:
    string name;
    int maxHp;
    int hp;
    int atk;
    int exp;
    int lvl;
    int lvlUp;
    int mapX, mapY, curX, curY, facing, money;
    // map stands for current room
    // cur stands for position in current room
    // facing ranges in {0, 1, 2, 3} which is {up, down, left, right}
    Backpack *bp;
    
public:
    /* Set & Get function*/
    void setMaxHp(int);
    void setHp(int);
    void setAtk(int);
    void setExp(int);
    void setLvl(int);
    void setLvlUp(int);
    int getMaxHp();
    int getHp();
    int getAtk();
    int getExp();
    int getLvl();
    int getLvlUp();
    Player();
    Player(string);
    void addItem(Item);
    void increaseStates(int,int,int);

    /* Set & Get function*/
    void setCurX(int);
    void setCurY(int);
    int getCurX();
    int getCurY();
    void setMapX(int);
    void setMapY(int);
    int getMapX();
    int getMapY();
    int getFacing();
    void setFacing(int);
    void setInventory(vector<Item>);
    vector<Item> getInventory();

    void showStatus();

    void gainExp(int);

    void recover();

    void showBackpack();
};

#endif // PLAYER_H_INCLUDED
